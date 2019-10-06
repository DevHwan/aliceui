#ifndef __APPLE__
#   error Apple platform only
#endif

#include <AUIDarwinAppImpl.h>
#include <AUIRasterWidgetManager.h>
#include <AUILinearLayoutWidget.h>
#include <AUIColorDrawable.h>
#include <AUIButtonWidget.h>
#include <AUIEditWidget.h>
#include <AUICheckboxWidget.h>
#include <AUIToggleWidget.h>
#include <AUISliderWidget.h>
#include <AUIApplication.h>

#include <core/SkSurface.h>

#include <iostream>
#include <memory>
#include <cassert>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#import <GLFW/glfw3.h>
#import <GLFW/glfw3native.h>

#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#import <simd/simd.h>

constexpr const auto kMetalShader = R"(
#include <metal_stdlib>

using namespace metal;

struct Vertex {
    packed_float4 position;
    packed_float2 texcoord;
};

struct ProjectedVertex {
    float4 position [[position]];
    float2 texcoord [[user(texcoords)]];
};

vertex ProjectedVertex vertex_main(device Vertex* vertices [[buffer(0)]],
                                   uint vid [[vertex_id]]) {

    float4 position = vertices[vid].position;
    float2 texcoord = vertices[vid].texcoord;

    ProjectedVertex out;
    out.position = position;
    out.texcoord = texcoord;
    return out;
}

fragment float4 fragment_main(ProjectedVertex in [[stage_in]],
                              texture2d<float, access::sample> tex [[texture(0)]],
                              sampler texsampler [[sampler(0)]]) {
    float4 color = tex.sample(texsampler, in.texcoord);
    return color;
}
)";

struct __attribute((packed)) Vertex {
    simd_float4 fPosition;
    simd_float2 fTexCoord;
};

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

constexpr const auto kMetalVertexMainFunc = "vertex_main";
constexpr const auto kMetalFragmentMainFunc = "fragment_main";

std::weak_ptr<AUIRasterWidgetManager> gWidgetManager;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    assert(window);
    
    auto pWidgetManager = gWidgetManager.lock();
    assert(pWidgetManager);
    
    const auto isShiftOn = !!(GLFW_MOD_SHIFT & mods);
    const auto isCtrlOn = !!(GLFW_MOD_CONTROL & mods);
    const auto isAltOn = !!(GLFW_MOD_ALT & mods);
    
    const auto isKeyDown = (GLFW_PRESS == action);
    const auto isKeyUp = (GLFW_RELEASE == action);
    
    unsigned int maskCode = AUIKeyboardEvent::kNone_MaskCode;
    maskCode |= (isShiftOn) ? AUIKeyboardEvent::kShiftOn_MaskCode : 0;
    maskCode |= (isCtrlOn) ? AUIKeyboardEvent::kCtrlOn_MaskCode : 0;
    maskCode |= (isAltOn) ? AUIKeyboardEvent::kAltOn_MaskCode : 0;

    AUIKeyboardEvent::EventType keyboardEventType = AUIKeyboardEvent::kUndefined_EventType;
    if (isKeyDown) {
        keyboardEventType = AUIKeyboardEvent::kKeyDown_EventType;
    } else if (isKeyUp) {
        keyboardEventType = AUIKeyboardEvent::kKeyUp_EventType;
    }
    
    const AUIKeyboardEvent keyboardEvent(keyboardEventType, static_cast<unsigned int>(scancode), static_cast<AUIKeyboardEvent::MaskCode>(maskCode));
    pWidgetManager->SendKeyboardEvent(keyboardEvent);
}

static void keyCharCallback(GLFWwindow* window, unsigned int codepoint) {
    assert(window);
    
    auto pWidgetManager = gWidgetManager.lock();
    assert(pWidgetManager);
    
    const AUIKeyboardEvent::EventType keyboardEventType = AUIKeyboardEvent::kChar_EventType;
    
    const AUIKeyboardEvent keyboardEvent(keyboardEventType, codepoint, AUIKeyboardEvent::kNone_MaskCode);
    pWidgetManager->SendKeyboardEvent(keyboardEvent);
}

static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    assert(window);
    
    auto pWidgetManager = gWidgetManager.lock();
    assert(pWidgetManager);
    
    const AUIMouseEvent mouseEvent(AUIMouseEvent::kMove_EventType, AUIMouseEvent::kNone_EventFlag, static_cast<int>(xpos), static_cast<int>(ypos));
    pWidgetManager->SendMouseEvent(mouseEvent);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    assert(window);
    
    auto pWidgetManager = gWidgetManager.lock();
    assert(pWidgetManager);
    
    const auto isButtonDown = (GLFW_PRESS == action);
    const auto isButtonUp = (GLFW_RELEASE == action);
    
    AUIMouseEvent::EventFlag mouseButtonEventFlag = AUIMouseEvent::kNone_EventFlag;
    AUIMouseEvent::EventType mouseButtonEventType = AUIMouseEvent::kUndefined_EventType;
    if (GLFW_MOUSE_BUTTON_LEFT == button) {
        mouseButtonEventFlag = AUIMouseEvent::kLBtn_EventFlag;
        if (isButtonDown)
            mouseButtonEventType = AUIMouseEvent::kLBtnDown_EventType;
        else if (isButtonUp)
            mouseButtonEventType = AUIMouseEvent::kLBtnUp_EventType;
    } else if (GLFW_MOUSE_BUTTON_RIGHT == button) {
        mouseButtonEventFlag = AUIMouseEvent::kRBtn_EventFlag;
        if (isButtonDown)
            mouseButtonEventType = AUIMouseEvent::kRBtnDown_EventType;
        else if (isButtonUp)
            mouseButtonEventType = AUIMouseEvent::kRBtnUp_EventType;    } else if (GLFW_MOUSE_BUTTON_MIDDLE == button) {
        mouseButtonEventFlag = AUIMouseEvent::kMBtn_EventFlag;
        if (isButtonDown)
            mouseButtonEventType = AUIMouseEvent::kMBtnDown_EventType;
        else if (isButtonUp)
            mouseButtonEventType = AUIMouseEvent::kMBtnUp_EventType;
    };
    
    double xpos = 0.0;
    double ypos = 0.0;
    glfwGetCursorPos(window, &xpos, &ypos);
    const AUIMouseEvent mouseEvent(mouseButtonEventType, mouseButtonEventFlag, static_cast<int>(xpos), static_cast<int>(ypos));
    pWidgetManager->SendMouseEvent(mouseEvent);
}

int main(int argc, const char* argv[]) {
	id<MTLDevice> mtlDevice = MTLCreateSystemDefaultDevice();
    if (nil == mtlDevice)
        return EXIT_FAILURE;
    
    if (!glfwInit())
        return EXIT_FAILURE;

    // Window creation hints
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);   // No rendering context
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    
    // Create window
    const auto window = glfwCreateWindow(kWindowWidth, kWindowHeight, "AliceUI Framework GLFW Metal Example", nullptr, nullptr);
    if (nullptr == window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // Setup callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, keyCharCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Get underlying native window
    NSWindow* nsWindow = glfwGetCocoaWindow(window);
    
    // Init Alice UI Framework
    AUIDarwinAppImpl::InitRootWindow(nsWindow);
    AUIApplicationAutoInit appAutoInit(std::make_unique<AUIDarwinAppImpl>());
    
    // Create raster widget manager
    auto pWidgetManager = std::make_shared<AUIRasterWidgetManager>();
    gWidgetManager = pWidgetManager;

    AUISlotPool signalPool;

    // Create root widget
    auto pRootLayout = std::make_shared<AUILinearLayoutWidget>();
    auto pBaseLayout = std::make_shared<AUILinearLayoutWidget>();
    auto pButton = std::make_shared<AUIButtonWidget>(L"Hello, World!");
    auto pEdit = std::make_shared<AUIEditWidget>(L"Edit here");
    auto pCheckBox = std::make_shared<AUICheckboxWidget>();
    auto pToggle = std::make_shared<AUIToggleWidget>();
    auto pSlider = std::make_shared<AUISliderWidget>();

    pEdit->SetDefaultSize(200.0f, 30.0f);
    pButton->SetDefaultSize(200.0f, 30.0f);

    // Connect edit callback event signal
    signalPool.Connect(pEdit->SignalCharChanged, [](AUIWidget *, const std::wstring& str, wchar_t) {
        std::wcout << L"Edit changed string : " << str << L'\n';
    });
    
    pBaseLayout->AddSubWidget(pButton);
    pBaseLayout->AddSubWidget(pEdit);
    pBaseLayout->AddSubWidget(pCheckBox);
    pBaseLayout->AddSubWidget(pToggle);
    pBaseLayout->AddSubWidget(pSlider);
    
    pRootLayout->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
    pRootLayout->AddSubWidget(pBaseLayout);
    pRootLayout->UpdateChildPosition();
    pRootLayout->UpdateSize();
    pWidgetManager->CreateInstance(pRootLayout);
    pRootLayout->SetDefaultSize(SkIntToScalar(kWindowWidth), SkIntToScalar(kWindowHeight));

    // Create skia surface
    auto pSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(kWindowWidth, kWindowHeight, SkAlphaType::kOpaque_SkAlphaType));

    // Time reference
    auto prevTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    
    // Setup input mode
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    
    
    CAMetalLayer* mtlLayer = [CAMetalLayer layer];
    mtlLayer.device = mtlDevice;
    mtlLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    nsWindow.contentView.layer = mtlLayer;
    nsWindow.contentView.wantsLayer = YES;

    const auto mtlCompileOptions = [MTLCompileOptions new];
    mtlCompileOptions.languageVersion = MTLLanguageVersion1_1;
    NSError* compileError = nil;
    id<MTLLibrary> mtlLibrary = [mtlDevice
                          newLibraryWithSource:[NSString stringWithUTF8String:kMetalShader]
                          options:mtlCompileOptions
                          error:&compileError];
    if (nil == mtlLibrary) {
        NSLog(@"can't create library: %@", compileError);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    id<MTLFunction> mtlVertexMainFunc = [mtlLibrary newFunctionWithName:[NSString stringWithUTF8String:kMetalVertexMainFunc]];
    id<MTLFunction> mtlFragmentMainFunc = [mtlLibrary newFunctionWithName:[NSString stringWithUTF8String:kMetalFragmentMainFunc]];
    id<MTLCommandQueue> mtlCommandQueue = [mtlDevice newCommandQueue];

    assert(mtlVertexMainFunc);
    assert(mtlFragmentMainFunc);
    assert(mtlCommandQueue);

    MTLRenderPipelineDescriptor* mtlRndrPipelineDesc = [MTLRenderPipelineDescriptor new];
    mtlRndrPipelineDesc.vertexFunction = mtlVertexMainFunc;
    mtlRndrPipelineDesc.fragmentFunction = mtlFragmentMainFunc;
    mtlRndrPipelineDesc.colorAttachments[0].pixelFormat = mtlLayer.pixelFormat;
    id<MTLRenderPipelineState> mtlRndrPipelineState = [mtlDevice newRenderPipelineStateWithDescriptor:mtlRndrPipelineDesc error:NULL];

    assert(mtlRndrPipelineState);
    
    // Create sampler state
    MTLSamplerDescriptor* mtlSamplerDesc = [MTLSamplerDescriptor new];
    mtlSamplerDesc.minFilter = MTLSamplerMinMagFilterNearest;
    mtlSamplerDesc.magFilter = MTLSamplerMinMagFilterLinear;
    mtlSamplerDesc.mipFilter = MTLSamplerMipFilterLinear;
    mtlSamplerDesc.sAddressMode = MTLSamplerAddressModeRepeat;
    mtlSamplerDesc.tAddressMode = MTLSamplerAddressModeRepeat;
    id<MTLSamplerState> mtlSamplerState = [mtlDevice newSamplerStateWithDescriptor:mtlSamplerDesc];
    
    // Create vertex buffer
    Vertex vertices[] = {
        { {-1.0f, -1.0f,  0.0f,  1.0f },  { 0.0f,  1.0f } },
        { { 1.0f, -1.0f,  0.0f,  1.0f },  { 1.0f,  1.0f } },
        { { 1.0f,  1.0f,  0.0f,  1.0f },  { 1.0f,  0.0f } },
        { {-1.0f, -1.0f,  0.0f,  1.0f },  { 0.0f,  1.0f } },
        { { 1.0f,  1.0f,  0.0f,  1.0f },  { 1.0f,  0.0f } },
        { {-1.0f,  1.0f,  0.0f,  1.0f },  { 0.0f,  0.0f } }
    };
    id<MTLBuffer> mtlVertexBuffer = [mtlDevice newBufferWithBytes:vertices length:sizeof(vertices) options:MTLResourceOptionCPUCacheModeDefault];
    [mtlVertexBuffer setLabel:@"Vertices"];
    
    // Create vertex descriptor
    MTLVertexDescriptor* mtlVertexDesc = [MTLVertexDescriptor vertexDescriptor];
    mtlVertexDesc.attributes[0].format = MTLVertexFormatFloat4;
    mtlVertexDesc.attributes[0].offset = 0;
    mtlVertexDesc.attributes[0].bufferIndex = 0;
    mtlVertexDesc.attributes[1].format = MTLVertexFormatFloat2;
    mtlVertexDesc.attributes[1].offset = offsetof(Vertex, fTexCoord);
    mtlVertexDesc.attributes[1].bufferIndex = 0;
    mtlVertexDesc.layouts[0].stride = sizeof(Vertex);
    
    // Texture
    id<MTLTexture> mtlTexture = nil;
    
    // Render pass descriptor
    MTLRenderPassDescriptor* mtlRndrPassDesc = [MTLRenderPassDescriptor new];
    MTLRenderPassColorAttachmentDescriptor* mtlRndrPassColorAttachDesc = mtlRndrPassDesc.colorAttachments[0];
    mtlRndrPassColorAttachDesc.loadAction = MTLLoadActionClear;
    mtlRndrPassColorAttachDesc.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);
    mtlRndrPassColorAttachDesc.storeAction = MTLStoreActionStore;

    while (!glfwWindowShouldClose(window))
    {
        int currentFBWidth, currentFBHeight;
        glfwGetFramebufferSize(window, &currentFBWidth, &currentFBHeight);

        do
        {
            // Update task
            AUIApplication::Instance().RunUpdateInstanceTask();
            AUIApplication::Instance().RunLazyUpdate();

            // Update time
            const auto currentTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            pWidgetManager->SendTickTimeEvent(prevTickTime, currentTickTime);
            prevTickTime = currentTickTime;

            // Update instances
            pWidgetManager->UpdateAllInstance();

            // Render
            pSurface->getCanvas()->clear(SkColorSetARGB(255, 255, 255, 255));
            pWidgetManager->Render(pSurface->getCanvas());
            const auto pImage = pSurface->makeImageSnapshot();
            if (nullptr == pImage)
                break;

            SkPixmap pixmap;
            if (false == pImage->peekPixels(&pixmap))
                break;

            if (nil == mtlTexture || (pixmap.width() != [mtlTexture width] || pixmap.height() != [mtlTexture height])) {
                MTLTextureDescriptor* mtlTextureDesc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm width:pixmap.width() height:pixmap.height() mipmapped:NO];
                mtlTexture = [mtlDevice newTextureWithDescriptor:mtlTextureDesc];
            }
            assert(mtlTexture);
            
            MTLRegion region = MTLRegionMake2D(0, 0, pixmap.width(), pixmap.height());
            [mtlTexture replaceRegion:region mipmapLevel:0 withBytes:pixmap.addr() bytesPerRow:pixmap.rowBytes()];
            
        } while (false);
        
        // Current rendering size
        mtlLayer.drawableSize = CGSizeMake(currentFBWidth, currentFBHeight);
        
        id<CAMetalDrawable> mtlNextDrawable = [mtlLayer nextDrawable];
        assert(mtlNextDrawable);
        
        // Set render pass color texture
        mtlRndrPassColorAttachDesc.texture = mtlNextDrawable.texture;

        id<MTLCommandBuffer> mtlCommandBuffer = [mtlCommandQueue commandBuffer];
        // Create render command
        id<MTLRenderCommandEncoder> mtlRndrCommandEncoder = [mtlCommandBuffer renderCommandEncoderWithDescriptor:mtlRndrPassDesc];
        
        [mtlRndrCommandEncoder setRenderPipelineState:mtlRndrPipelineState];
        // Set vertex stage
        [mtlRndrCommandEncoder setVertexBuffer:mtlVertexBuffer offset:0 atIndex:0];
        // Set fragment stage
        [mtlRndrCommandEncoder setFragmentTexture:mtlTexture atIndex:0];
        [mtlRndrCommandEncoder setFragmentSamplerState:mtlSamplerState atIndex:0];
        
        // Draw
        [mtlRndrCommandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];

        [mtlRndrCommandEncoder endEncoding];
        
        // Set command buffer
        [mtlCommandBuffer presentDrawable:mtlNextDrawable];
        
        // Commit
        [mtlCommandBuffer commit];
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        const auto key = glfwGetKey(window, GLFW_KEY_ESCAPE);
        if (key == GLFW_PRESS) {
            break;
        }
    }
    
    glfwDestroyWindow(window);

    glfwTerminate();
    
    return EXIT_SUCCESS;
}
