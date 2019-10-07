#include "AUIDarwinWindowHandle.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface AUIWindowDelegate : NSObject<NSWindowDelegate>

- (AUIWindowDelegate*)initWithWindow:(AUIDarwinWindowHandle*)initWindowHandle;

@end

@interface AUIWindowMainView : NSView

- (AUIWindowMainView*)initWithWindow:(AUIDarwinWindowHandle*)initWindow;

@end

@implementation AUIWindowDelegate {
    AUIDarwinWindowHandle* fWindowHandle;
}

- (AUIWindowDelegate *)initWithWindow:(AUIDarwinWindowHandle *)initWindowHandle {
    fWindowHandle = initWindowHandle;
    return self;
}

- (void)windowDidResize:(NSNotification *)notification {
    const NSRect mainRect = [((NSWindow*)fWindowHandle->Window()).contentView bounds];

    fWindowHandle->SetSize(mainRect.size.width, mainRect.size.height);
    fWindowHandle->Invalidate();
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    fWindowHandle->Deactivate();
    return NO;
}

@end

@implementation AUIWindowMainView {
    AUIDarwinWindowHandle* fWindowHandle;
    NSTrackingArea* fTrackingArea;
}

- (AUIWindowMainView *)initWithWindow:(AUIDarwinWindowHandle *)initWindow {
    self = [super init];

    fWindowHandle = initWindow;
    fTrackingArea = nil;

    [self updateTrackingAreas];

    return self;
}

- (void)dealloc {
    [fTrackingArea release];
    [super dealloc];
}

- (BOOL)isOpaque {
    return YES;
}

- (BOOL)canBecomeKeyView {
    return YES;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)updateTrackingAreas {
    if (fTrackingArea != nil) {
        [self removeTrackingArea:fTrackingArea];
        [fTrackingArea release];
    }

    const NSTrackingAreaOptions options = NSTrackingMouseEnteredAndExited |
                                          NSTrackingActiveInKeyWindow |
                                          NSTrackingEnabledDuringMouseDrag |
                                          NSTrackingCursorUpdate |
                                          NSTrackingInVisibleRect |
                                          NSTrackingAssumeInside;

    fTrackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                                options:options
                                                  owner:self
                                               userInfo:nil];

    [self addTrackingArea:fTrackingArea];
    [super updateTrackingAreas];
}

- (void)keyDown:(NSEvent *)event {
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Keyboard Event
    //AUIKeyboardEvent keyEvent;
    //pWidgetManager->SendKeyboardEvent(keyEvent);
}

- (void)keyUp:(NSEvent *)event {
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Keyboard Event
    //AUIKeyboardEvent keyEvent;
    //pWidgetManager->SendKeyboardEvent(keyEvent);
}

- (void)mouseDown:(NSEvent *)event {
    const NSPoint pos = [event locationInWindow];
    const NSRect rect = [((NSWindow*)fWindowHandle->Window()).contentView frame];
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Mouse event
    //AUIMouseEvent mouseEvent;
    //pWidgetManager->SendMouseEvent(mouseEvent);
}

- (void)mouseUp:(NSEvent *)event {
    const NSPoint pos = [event locationInWindow];
    const NSRect rect = [((NSWindow*)fWindowHandle->Window()).contentView frame];
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Mouse event
    //AUIMouseEvent mouseEvent;
    //pWidgetManager->SendMouseEvent(mouseEvent);
}

- (void)mouseDragged:(NSEvent *)event {
    [self mouseMoved:event];
}

- (void)mouseMoved:(NSEvent *)event {
    const NSPoint pos = [event locationInWindow];
    const NSRect rect = [((NSWindow*)fWindowHandle->Window()).contentView frame];
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Mouse event
    //AUIMouseEvent mouseEvent;
    //pWidgetManager->SendMouseEvent(mouseEvent);
}

- (void)scrollWheel:(NSEvent *)event {
    const NSPoint pos = [event locationInWindow];
    const NSRect rect = [((NSWindow*)fWindowHandle->Window()).contentView frame];
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Mouse event
    //AUIMouseEvent mouseEvent;
    //pWidgetManager->SendMouseEvent(mouseEvent);
}

- (void)drawRect:(NSRect)rect {
    [super drawRect:rect];
    NSLog(@"Paint region : %@", NSStringFromRect(rect));
    AUIRasterWidgetManager* pWidgetManager = fWindowHandle->GetWidgetManager();
    // TODO: Render
    //pWidgetManager->Render();
}

@end

AUIDarwinWindowHandle::AUIDarwinWindowHandle()
: m_pWidgetManager(std::make_unique<AUIRasterWidgetManager>()) {
    this->InitializeWindow();
}

AUIDarwinWindowHandle::~AUIDarwinWindowHandle() {
    this->FinalizeWindow();
}

bool AUIDarwinWindowHandle::InitializeWindow() {
    AUIWindowDelegate* delegate = [[AUIWindowDelegate alloc] initWithWindow:this];
    if (nil == delegate) {
        return false;
    }
    
    // Initial window size
    NSRect windowRect = NSMakeRect(0, 0, 1, 1);
    
    // Window style flags
    NSUInteger windowStyle = (NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskResizable|NSWindowStyleMaskMiniaturizable);
    
    fWindow = [[NSWindow alloc] initWithContentRect:windowRect styleMask:windowStyle backing:NSBackingStoreBuffered defer:NO];
    if (nil == fWindow) {
        [delegate release];
        return false;
    }
    [(NSWindow*)fWindow setOpaque:NO];
    [(NSWindow*)fWindow setBackgroundColor:[NSColor whiteColor]];
    
    AUIWindowMainView* view = [[AUIWindowMainView alloc] initWithWindow:this];
    if (nil == view) {
        [(NSWindow*)fWindow release];
        [delegate release];
        return false;
    }
    
    [(NSWindow*)fWindow setContentView:view];
    [(NSWindow*)fWindow makeFirstResponder:view];
    [(NSWindow*)fWindow setDelegate:delegate];
    [(NSWindow*)fWindow setAcceptsMouseMovedEvents:YES];
    [(NSWindow*)fWindow setRestorable:NO];
    
    // Should be retained by window now
    [view release];

    this->SetNative(fWindow);

    return true;
}

bool AUIDarwinWindowHandle::FinalizeWindow() {
    if (nil != fWindow) {
        [(NSWindow*)fWindow close];
        fWindow = nil;
        this->SetNative(nullptr);
    }
    return true;
}

void AUIDarwinWindowHandle::SetRootWidget(const std::shared_ptr<AUIWidget> &pWidget) {
    if (this->m_pWidget == pWidget )
        return;
    
    if (pWidget) {
        if (pWidget->IsCreated()) {
            AUIAssertFailReason("Already created!!");
            return;
        }
    }

    // Remove previous
    if (this->m_pWidget) {
        if (this->m_pWidget->IsCreated()) {
            this->m_pWidgetManager->DestroyInstance(this->m_pWidget);
        }
    }

    // Set & Create
    this->m_pWidget = pWidget;
    if (this->m_pWidget)
        this->m_pWidgetManager->CreateInstance(this->m_pWidget);
    this->m_pWidgetManager->SetFocusTarget(this->m_pWidget);
}

void AUIDarwinWindowHandle::Activate(AUIHandle *const pParent) {
    NSLog(@"Activate frame : %@", NSStringFromRect([(NSWindow*)fWindow frame]));
}

void AUIDarwinWindowHandle::ActivateModal(AUIHandle *const pParent) {

}

void AUIDarwinWindowHandle::Deactivate() {

}

void AUIDarwinWindowHandle::SetMinSize(int width, int height) {
    ((NSWindow*)fWindow).minSize = NSMakeSize(width, height);
}

void AUIDarwinWindowHandle::SetMaxSize(int width, int height) {
    ((NSWindow*)fWindow).maxSize = NSMakeSize(width, height);
}

void AUIDarwinWindowHandle::SetTransparent(bool val) {
    [(NSWindow*)fWindow setOpaque:val];
}

bool AUIDarwinWindowHandle::IsTransparent() const {
    return [(NSWindow*)fWindow isOpaque];
}
