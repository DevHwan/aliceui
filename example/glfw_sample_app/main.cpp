#if defined(WIN32)
#   include <WinSDKVer.h>
#   define NOMINMAX
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#   define GLFW_EXPOSE_NATIVE_WIN32
#   include <AUIWin32AppImpl.h>
#elif defined(__APPLE__)
#   define GLFW_EXPOSE_NATIVE_COCOA
#   include <AUIDarwinAppImpl.h>
#endif

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

#include <glm/glm.hpp>

#include <iostream>
#include <memory>

#include "Shader.h"
#include "ShaderProgram.h"
#include "QuadModel.h"
#include "CubeModel.h"
#include "Texture2D.h"
#include "SampleState.h"

constexpr auto kDefaultVertexShaderCode = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 oTexCoord;

uniform mat4 uMatModelView;
uniform mat4 uMatProjection;

void main() {
    oTexCoord = texcoord;
    gl_Position = uMatProjection * uMatModelView * vec4(position, 1.0);
}
)";

constexpr auto kTextureFragmentShaderCode = R"(
#version 330 core

in vec2 oTexCoord;

out vec4 color;

uniform sampler2D uTexture;

void main() {
    color = texture(uTexture, oTexCoord);
}
)";

constexpr const int kWindowWidth = 1280;
constexpr const int kWindowHeight = 720;
constexpr const GLfloat kWindowAspectRatio = static_cast<GLfloat>(kWindowHeight) / static_cast<GLfloat>(kWindowWidth);

constexpr const int kWidgetWidth = kWindowWidth;
constexpr const int kWidgetHeight = kWindowHeight;
constexpr const GLfloat kWidget2WindowRatio = static_cast<GLfloat>(kWindowWidth) / static_cast<GLfloat>(kWidgetWidth);

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

#if defined(_WIN32)
    const auto mappedVK = MapVirtualKeyW(scancode, MAPVK_VSC_TO_VK);
    if (0 != mappedVK)
        scancode = mappedVK;
#endif

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

int main() {
    // Initialize GLFW3
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3\n";
        return EXIT_FAILURE;
    }

    // Set context hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
#endif
    
    // Create window
    const auto window = glfwCreateWindow(kWindowWidth, kWindowHeight, "AliceUI Framework GLFW Example", nullptr, nullptr);
    if (nullptr == window) {
        std::cerr << "Failed to create GLFW window.";
        return EXIT_FAILURE;
    }

    // Setup callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, keyCharCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Init Alice UI Framework
#if defined(WIN32)
    AUIWin32AppImpl::InitRootWindow(glfwGetWin32Window(window));
    AUIApplicationAutoInit appAutoInit(std::make_unique<AUIWin32AppImpl>());
#elif defined(__APPLE__)
    AUIDarwinAppImpl::InitRootWindow(glfwGetCocoaWindow(window));
    AUIApplicationAutoInit appAutoInit(std::make_unique<AUIDarwinAppImpl>());
#endif

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
    
    pBaseLayout->SetBackgroundDrawable(std::make_shared<AUIColorDrawable>(SK_ColorWHITE));
    pBaseLayout->AddSubWidget(pButton);
    pBaseLayout->AddSubWidget(pEdit);
    pBaseLayout->AddSubWidget(pCheckBox);
    pBaseLayout->AddSubWidget(pToggle);
    pBaseLayout->AddSubWidget(pSlider);
    
    pRootLayout->SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    pRootLayout->AddSubWidget(pBaseLayout);
    pRootLayout->UpdateChildPosition();
    pRootLayout->UpdateSize();
    pWidgetManager->CreateInstance(pRootLayout);
    pRootLayout->SetDefaultSize(SkIntToScalar(kWidgetWidth), SkIntToScalar(kWidgetHeight));

    // Create skia surface
    auto pSurface = SkSurface::MakeRaster(SkImageInfo::MakeN32(kWindowWidth, kWindowHeight, SkAlphaType::kOpaque_SkAlphaType));

    // Time reference
    auto prevTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cerr << "Failed to initialize GLEW\n";
        return EXIT_FAILURE;
    }

    Shader vertexShader;
    if (false == vertexShader.CreateVertexShader(kDefaultVertexShaderCode)) {
        std::cerr << "Failed to create vertex shader\n";
        return EXIT_FAILURE;
    }

    Shader texFragmentShader;
    if (false == texFragmentShader.CreateFragmentShader(kTextureFragmentShaderCode)) {
        std::cerr << "Failed to create fragment shader\n";
        return EXIT_FAILURE;
    }

    ShaderProgram shaderProgram;
    if (false == shaderProgram.Create(vertexShader, texFragmentShader)) {
        std::cerr << "Failed to create shader program\n";
        return EXIT_FAILURE;
    }

    QuadModel quadModel;
    if (false == quadModel.Create()) {
        std::cerr << "Failed to create quad model\n";
        return EXIT_FAILURE;
    }
    
    CubeModel cubeModel;
    if (false == cubeModel.Create()) {
        std::cerr << "Failed to create cube model\n";
        return EXIT_FAILURE;
    }

    Texture2D texture;
    if (false == texture.Create()) {
        std::cerr << "Failed to create texture\n";
        return EXIT_FAILURE;
    }

    Texture2D cubeTexture;
    if (false == cubeTexture.Create()) {
        std::cerr << "Failed to create cube texture\n";
        return EXIT_FAILURE;
    }
    {
        auto pTextureSurface = SkSurface::MakeRaster(SkImageInfo::Make(256, 256, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType));
        constexpr const auto baseSize = 256.0f / 3.0f;
        
        auto pTextureCanvas = pTextureSurface->getCanvas();
        pTextureCanvas->clear(SkColorSetARGB(255, 123, 45, 67));
        SkPaint paint;
        paint.setColor(SK_ColorRED);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 0.0f, baseSize * 0.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorBLUE);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 1.0f, baseSize * 0.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorCYAN);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 2.0f, baseSize * 0.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorGRAY);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 0.0f, baseSize * 1.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorGREEN);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 1.0f, baseSize * 1.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorYELLOW);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 2.0f, baseSize * 1.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorMAGENTA);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 0.0f, baseSize * 2.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorDKGRAY);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 1.0f, baseSize * 2.0f, baseSize, baseSize), paint);
        paint.setColor(SK_ColorBLACK);
        pTextureCanvas->drawRect(SkRect::MakeXYWH(baseSize * 2.0f, baseSize * 2.0f, baseSize, baseSize), paint);

        auto pImage = pTextureSurface->makeImageSnapshot();
        
        SkPixmap pixmap;
        if (pImage->peekPixels(&pixmap)) {
            cubeTexture.UpdateImage(pixmap);
        } else {
            std::cerr << "Failed to upload texture\n";
            return EXIT_FAILURE;
        }
    }

    SampleState samplerState;
    if (false == samplerState.Create()) {
        std::cerr << "Failed to create sampler state\n";
        return EXIT_FAILURE;
    }

    // Set depth function
    glDepthFunc(GL_LEQUAL);
    
    // Matrix
    auto matModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    const auto matView = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const auto matProjection = glm::frustum(-2.0f, 2.0f, -2.0f * kWindowAspectRatio, 2.0f * kWindowAspectRatio, 1.0f, 100.0f);


    const auto matUIModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    const auto matUIView = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const auto matUIProjection = glm::frustum(-kWidget2WindowRatio, kWidget2WindowRatio, -kWidget2WindowRatio, kWidget2WindowRatio, 1.0f, 100.0f);
    const auto matUIModelView = matUIView * matUIModel;
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    assert(GL_NO_ERROR == glGetError());

    GLfloat rotationUpdate = 0.0f;
    while (!glfwWindowShouldClose(window)) {

        rotationUpdate += 0.01f;
        matModel = glm::rotate(glm::mat4(1.0f), rotationUpdate, glm::vec3(1.0f, 1.0f, 1.0f));
        const auto matModelView = matView * matModel;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        assert(GL_NO_ERROR == glGetError());

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

            pRootLayout->GetWidth();
            pRootLayout->GetHeight();
            
            // Render
            pSurface->getCanvas()->clear(SkColorSetARGB(255, 255, 255, 255));
            pWidgetManager->Render(pSurface->getCanvas());
            const auto pImage = pSurface->makeImageSnapshot();
            if (nullptr == pImage)
                break;

            SkPixmap pixmap;
            if (false == pImage->peekPixels(&pixmap))
                break;

            texture.UpdateImage(pixmap);

        } while (false);


        // Render in OpenGL

        shaderProgram.UseProgram();
        {
            // Don't use depth test
            glDisable(GL_DEPTH_TEST);

            shaderProgram.BindTexture(texture, samplerState, "uTexture", 0);
            shaderProgram.SetUniform("uMatModelView", matUIModelView);
            shaderProgram.SetUniform("uMatProjection", matUIProjection);
            shaderProgram.SetUniform("uDiscardTransparent", 1);

            quadModel.Draw();
            
            // Use depth test
            glEnable(GL_DEPTH_TEST);

            shaderProgram.BindTexture(cubeTexture, samplerState, "uTexture", 0);
            shaderProgram.SetUniform("uMatModelView", matModelView);
            shaderProgram.SetUniform("uMatProjection", matProjection);

            cubeModel.Draw();
        }
        shaderProgram.UnuseProgram();

        glfwSwapBuffers(window);
        glfwPollEvents();

        const auto key = glfwGetKey(window, GLFW_KEY_ESCAPE);
        if (key == GLFW_PRESS) {
            break;
        }
    }

    // Terminate
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
