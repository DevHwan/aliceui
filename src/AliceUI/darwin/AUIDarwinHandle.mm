#include "pch.h"
#include "AUIDarwinHandle.h"
#include "AUIStringConvert.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

AUIDarwinHandle::AUIDarwinHandle(void* native) noexcept
    : fNative(native)
{
    AUIAssert(native);
}

void AUIDarwinHandle::SetTitle(const std::wstring& title)
{
    const auto utf8Title = AUIStringConvert::WCSToUTF8(title);
    [(NSWindow*)fNative setTitle:[NSString stringWithUTF8String:utf8Title.c_str()]];
}

void AUIDarwinHandle::Activate(AUIHandle* const pParent)
{
    // TODO
}

void AUIDarwinHandle::ActivateModal(AUIHandle* const pParent)
{
    // TODO
    
}

void AUIDarwinHandle::Deactivate()
{
    
    // TODO
}

bool AUIDarwinHandle::IsActivated() const
{
    // TODO
    return true;
}

void AUIDarwinHandle::DoShowMinimized()
{
    // TODO
    
}

void AUIDarwinHandle::DoShowMaximized()
{
    // TODO
    
}

void AUIDarwinHandle::DoShowDefault()
{
    // TODO
    
}

void AUIDarwinHandle::Invalidate()
{
    
    // TODO
}

void AUIDarwinHandle::UpdateWindow()
{
    
    // TODO
}

void AUIDarwinHandle::SetVisible(bool state)
{
    // TODO
    
}

void AUIDarwinHandle::SetFocus()
{
    // TODO
    
}

void AUIDarwinHandle::CaptureMouseEvent()
{
    // TODO
    
}

void AUIDarwinHandle::ReleaseMouseEvent()
{
    // TODO
    
}

void AUIDarwinHandle::SetOpacity(const SkAlpha alpha)
{
    // TODO
    
}

bool AUIDarwinHandle::IsZoomed() const
{
    
    // TODO
    return false;
}

bool AUIDarwinHandle::IsIconic() const
{
    // TODO
    return false;
}

void AUIDarwinHandle::SetResizeable(bool val)
{
    
    // TODO
}

bool AUIDarwinHandle::IsResizeable() const
{
    // TODO
    return true;
}

void AUIDarwinHandle::SetSize(int width, int height)
{
    [(NSWindow*)fNative setContentSize:NSMakeSize((CGFloat)width, (CGFloat)height)];
}

void AUIDarwinHandle::SetPosition(int x, int y)
{
    [(NSWindow*)fNative setFrameOrigin:NSMakePoint((CGFloat)x, (CGFloat)y)];
}

void AUIDarwinHandle::SetPositionAndSize(int x, int y, int sx, int sy)
{
    [(NSWindow*)fNative setFrameOrigin:NSMakePoint((CGFloat)x, (CGFloat)y)];
    [(NSWindow*)fNative setContentSize:NSMakeSize((CGFloat)sx, (CGFloat)sy)];
}

void AUIDarwinHandle::GetSize(int& width, int& height)
{
    const auto winsize = [[(NSWindow*)fNative contentView] frame].size;
    width = (int)winsize.width;
    height = (int)winsize.height;
}

void AUIDarwinHandle::GetPosition(int& x, int& y)
{
    const auto pos = [[(NSWindow*)fNative contentView] frame].origin;
    x = (int)pos.x;
    y = (int)pos.y;
}

void AUIDarwinHandle::GetPositionAndSize(int& x, int& y, int& sx, int& sy)
{
    const auto windowFrame = [[(NSWindow*)fNative contentView] frame];
    sx = (int)windowFrame.size.width;
    sy = (int)windowFrame.size.height;
    x = (int)windowFrame.origin.x;
    y = (int)windowFrame.origin.y;
}

void AUIDarwinHandle::BeginModal()
{
    // TODO
}

void AUIDarwinHandle::EndModal(int result)
{
    // TODO
}
