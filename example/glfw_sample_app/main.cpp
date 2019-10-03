#include <AUIRasterWidgetManager.h>
#include <AUILinearLayoutWidget.h>
#include <AUIColorDrawable.h>
#include <AUIButtonWidget.h>
#include <AUIApplication.h>

#include <core/SkSurface.h>

#if defined(WIN32)
#   define GLFW_EXPOSE_NATIVE_WIN32
#   include <AUIWin32AppImpl.h>
#elif defined(__APPLE__)
#   define GLFW_EXPOSE_NATIVE_COCOA
#   include <AUIDarwinAppImpl.h>
#endif

#include <iostream>
#include <memory>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "QuadModel.h"
#include "SampleState.h"

constexpr auto kDefaultVertexShaderCode = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 oTexCoord;

void main() {
    oTexCoord = texcoord;

    gl_Position.xyz = position;
    gl_Position.w = 1.0;
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

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

std::unique_ptr<AUIRasterWidgetManager> gWidgetManager;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    assert(window);
    assert(gWidgetManager);
    
}

static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    assert(window);
    assert(gWidgetManager);
    AUIMouseEvent mouseEvent(AUIMouseEvent::kMove_EventType, AUIMouseEvent::kNone_EventFlag, static_cast<int>(xpos), static_cast<int>(ypos));
    gWidgetManager->SendMouseEvent(mouseEvent);
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
    glfwSetCursorPosCallback(window, cursorCallback);
    
    // Init Alice UI Framework
#if defined(WIN32)
    AUIWin32AppImpl::InitRootWindow(glfwGetWin32Window(window));
    AUIApplicationAutoInit appAutoInit(std::make_unique<AUIWin32AppImpl>());
#elif defined(__APPLE__)
    AUIDarwinAppImpl::InitRootWindow(glfwGetCocoaWindow(window));
    AUIApplicationAutoInit appAutoInit(std::make_unique<AUIDarwinAppImpl>());
#endif

    // Create raster widget manager
    gWidgetManager.reset(new AUIRasterWidgetManager());

    // Create root widget
    auto pRootLayout = std::make_shared<AUILinearLayoutWidget>();
    auto pButton = std::make_shared<AUIButtonWidget>(L"Hello, World!");
    pButton->SetDefaultSize(200.0f, 30.0f);
    pRootLayout->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
    pRootLayout->AddSubWidget(pButton);
    pRootLayout->UpdateChildPosition();
    pRootLayout->UpdateSize();
    gWidgetManager->CreateInstance(pRootLayout);
    pRootLayout->SetDefaultSize(SkIntToScalar(kWindowWidth), SkIntToScalar(kWindowHeight));

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

    ShaderProgram texProgram;
    if (false == texProgram.Create(vertexShader, texFragmentShader)) {
        std::cerr << "Failed to create shader program\n";
        return EXIT_FAILURE;
    }

    QuadModel quadModel;
    if (false == quadModel.Create()) {
        std::cerr << "Failed to create model\n";
        return EXIT_FAILURE;
    }

    Texture2D texture;
    if (false == texture.Create()) {
        std::cerr << "Failed to create texture\n";
        return EXIT_FAILURE;
    }

    SampleState samplerState;
    if (false == samplerState.Create()) {
        std::cerr << "Failed to create sampler state\n";
        return EXIT_FAILURE;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    assert(GL_NO_ERROR == glGetError());

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        assert(GL_NO_ERROR == glGetError());

        do
        {
            // Update task
            AUIApplication::Instance().RunUpdateInstanceTask();
            AUIApplication::Instance().RunLazyUpdate();

            // Update time
            const auto currentTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            gWidgetManager->SendTickTimeEvent(prevTickTime, currentTickTime);
            prevTickTime = currentTickTime;

            // Update instances
            gWidgetManager->UpdateAllInstance();

            // Render
            pSurface->getCanvas()->clear(SkColorSetARGB(255, 255, 255, 255));
            gWidgetManager->Render(pSurface->getCanvas());
            const auto pImage = pSurface->makeImageSnapshot();
            if (nullptr == pImage)
                break;

            SkPixmap pixmap;
            if (false == pImage->peekPixels(&pixmap))
                break;

            texture.UpdateImage(pixmap);

        } while (false);


        // Render in OpenGL

        texProgram.UseProgram();
        {
            texProgram.BindTexture(texture, samplerState, "uTexture", 0);
            quadModel.Draw();
        }
        texProgram.UnuseProgram();

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
