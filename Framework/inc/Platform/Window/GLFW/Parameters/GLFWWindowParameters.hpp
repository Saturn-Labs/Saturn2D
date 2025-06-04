#pragma once
#include "ClientAPI.hpp"
#include "ContextCreationAPI.hpp"
#include "ContextReleaseBehavior.hpp"
#include "ContextRobustness.hpp"
#include "OpenGLProfile.hpp"
#include "Core/Window/Parameters/WindowParameters.hpp"

namespace Saturn::Platform::GLFW {
    struct GLFWWindowParameters final : public WindowParameters {
        GLFWmonitor* monitor = nullptr;
        GLFWwindow* share = nullptr;
        bool resizable = true;
        bool visible = true;
        bool decorated = true;
        bool focused = true;
        bool autoIconify = true;
        bool floating = false;
        bool maximized = false;
        bool centerCursor = true;
        bool transparentFramebuffer = false;
        bool focusOnShow = true;
        bool scaleToMonitor = false;
        i32 redBits = 8;
        i32 greenBits = 8;
        i32 blueBits = 8;
        i32 alphaBits = 8;
        i32 depthBits = 24;
        i32 stencilBits = 8;
        i32 accumRedBits = 0;
        i32 accumGreenBits = 0;
        i32 accumBlueBits = 0;
        i32 accumAlphaBits = 0;
        i32 auxBuffers = 0;
        i32 samples = 0;
        i32 refreshRate = -1;
        bool stereoscopic = false;
        bool srgbCapable = false;
        bool doubleBuffer = true;
        ClientAPI clientApi = ClientAPI::OpenGL;
        ContextCreationAPI contextCreation = ContextCreationAPI::NativeContext;
        i32 contextVersionMajor = 1;
        i32 contextVersionMinor = 0;
        ContextRobustness contextRobustness = ContextRobustness::NoRobustness;
        ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
        bool forwardCompatibility = false;
#ifdef DEBUG_BUILD
        bool debugContext = true;
#else
        bool debugContext = false;
#endif
        OpenGLProfile openGLProfile = OpenGLProfile::Any;
        bool cocoaRetinaFramebuffer = true;
        String cocoaFrameName;
        bool cocoaGraphicsSwitching = false;
        String x11ClassName;
        String x11InstanceName;
        bool contextNoError = false;
        ~GLFWWindowParameters() override = default;
    };
}
