#pragma once
#include "ClientAPI.hpp"
#include "ContextCreationAPI.hpp"
#include "ContextReleaseBehavior.hpp"
#include "ContextRobustness.hpp"
#include "OpenGLProfile.hpp"
#include "Core/Window/WindowProperties.hpp"

namespace Saturn {
    struct GLFWWindowProperties final : public WindowProperties {
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
        int redBits = 8;
        int greenBits = 8;
        int blueBits = 8;
        int alphaBits = 8;
        int depthBits = 24;
        int stencilBits = 8;
        int accumRedBits = 0;
        int accumGreenBits = 0;
        int accumBlueBits = 0;
        int accumAlphaBits = 0;
        int auxBuffers = 0;
        int samples = 0;
        int refreshRate = -1;
        bool stereoscopic = false;
        bool srgbCapable = false;
        bool doubleBuffer = true;
        ClientAPI clientApi = ClientAPI::OpenGL;
        ContextCreationAPI contextCreation = ContextCreationAPI::NativeContext;
        int contextVersionMajor = 1;
        int contextVersionMinor = 0;
        ContextRobustness contextRobustness = ContextRobustness::NoRobustness;
        ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
        bool forwardCompatibility = false;
        bool debugContext = false;
        OpenGLProfile openGLProfile = OpenGLProfile::Any;
        bool cocoaRetinaFramebuffer = true;
        std::string cocoaFrameName;
        bool cocoaGraphicsSwitching = false;
        std::string x11ClassName;
        std::string x11InstanceName;
        bool contextNoError = false;
        ~GLFWWindowProperties() override = default;
    };
}
