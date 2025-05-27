#include "Precompiled.hpp"
#include "Core/Window/GLFW/GLFWWindow.hpp"

#include <stdexcept>

#include "Core/Window/GLFW/WindowProps/GLFWWindowProperties.hpp"

namespace Saturn {
    GLFWWindow::GLFWWindow(const WindowProperties& properties) :
        IWindow(),
        _windowHandle(nullptr)
    {
        GLFWmonitor* monitor = nullptr;
        GLFWwindow* share = nullptr;
        bool modifiedHints = false;
        if (auto* glfwProps = dynamic_cast<const GLFWWindowProperties*>(&properties)) {
            modifiedHints = true;
            monitor = glfwProps->monitor;
            share = glfwProps->share;

            // Sets all glfw window hints
            glfwWindowHint(GLFW_RESIZABLE, glfwProps->resizable);
            glfwWindowHint(GLFW_VISIBLE, glfwProps->visible);
            glfwWindowHint(GLFW_DECORATED, glfwProps->decorated);
            glfwWindowHint(GLFW_FOCUSED, glfwProps->focused);
            glfwWindowHint(GLFW_AUTO_ICONIFY, glfwProps->autoIconify);
            glfwWindowHint(GLFW_FLOATING, glfwProps->floating);
            glfwWindowHint(GLFW_MAXIMIZED, glfwProps->maximized);
            glfwWindowHint(GLFW_CENTER_CURSOR, glfwProps->centerCursor);
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, glfwProps->transparentFramebuffer);
            glfwWindowHint(GLFW_FOCUS_ON_SHOW, glfwProps->focusOnShow);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, glfwProps->scaleToMonitor);
            glfwWindowHint(GLFW_RED_BITS, glfwProps->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, glfwProps->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, glfwProps->blueBits);
            glfwWindowHint(GLFW_ALPHA_BITS, glfwProps->alphaBits);
            glfwWindowHint(GLFW_DEPTH_BITS, glfwProps->depthBits);
            glfwWindowHint(GLFW_STENCIL_BITS, glfwProps->stencilBits);
            glfwWindowHint(GLFW_ACCUM_RED_BITS, glfwProps->accumRedBits);
            glfwWindowHint(GLFW_ACCUM_GREEN_BITS, glfwProps->accumGreenBits);
            glfwWindowHint(GLFW_ACCUM_BLUE_BITS, glfwProps->accumBlueBits);
            glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, glfwProps->accumAlphaBits);
            glfwWindowHint(GLFW_AUX_BUFFERS, glfwProps->auxBuffers);
            glfwWindowHint(GLFW_SAMPLES, glfwProps->samples);
            glfwWindowHint(GLFW_REFRESH_RATE, glfwProps->refreshRate);
            glfwWindowHint(GLFW_STEREO, glfwProps->stereoscopic);
            glfwWindowHint(GLFW_SRGB_CAPABLE, glfwProps->srgbCapable);
            glfwWindowHint(GLFW_DOUBLEBUFFER, glfwProps->doubleBuffer);
            glfwWindowHint(GLFW_CLIENT_API, static_cast<int>(glfwProps->clientApi));
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, static_cast<int>(glfwProps->contextCreation));
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwProps->contextVersionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwProps->contextVersionMinor);
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(glfwProps->contextRobustness));
            glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, static_cast<int>(glfwProps->contextReleaseBehavior));
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, glfwProps->forwardCompatibility);
            glfwWindowHint(GLFW_CONTEXT_DEBUG, glfwProps->debugContext);
            glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(glfwProps->openGLProfile));
            glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, glfwProps->cocoaRetinaFramebuffer);
            glfwWindowHintString(GLFW_COCOA_FRAME_NAME, glfwProps->cocoaFrameName.c_str());
            glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, glfwProps->cocoaGraphicsSwitching);
            glfwWindowHintString(GLFW_X11_CLASS_NAME, glfwProps->x11ClassName.c_str());
            glfwWindowHintString(GLFW_X11_INSTANCE_NAME, glfwProps->x11InstanceName.c_str());
            glfwWindowHint(GLFW_CONTEXT_NO_ERROR, glfwProps->contextNoError);
        }

        _windowHandle = glfwCreateWindow(
            static_cast<int>(properties.width),
            static_cast<int>(properties.height),
            properties.title.c_str(),
            monitor,
            share
        );

        if (!_windowHandle.getGlfwHandle()) {
            throw std::runtime_error("Failed to create GLFW window!");
        }

        if (modifiedHints)
            glfwDefaultWindowHints();

        auto* lastContext = glfwGetCurrentContext();
        setContextCurrent();
        glfwSwapInterval(0);
        glfwMakeContextCurrent(lastContext);
    }

    GLFWWindow::~GLFWWindow() {
        glfwDestroyWindow(_windowHandle.getGlfwHandle());
    }

    NativeWindowHandle GLFWWindow::getNativeHandle() const {
        return _windowHandle;
    }

    bool GLFWWindow::isValid() {
        return _windowHandle.getGlfwHandle() && !glfwWindowShouldClose(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::pollEvents() {
        if (!isValid())
            return;

        if (glfwGetCurrentContext() != _windowHandle.getGlfwHandle())
            setContextCurrent();

        glfwPollEvents();
    }

    void GLFWWindow::swapBuffers() {
        if (!isValid())
            return;
        glfwSwapBuffers(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::setContextCurrent() {
        if (!isValid())
            return;
        glfwMakeContextCurrent(_windowHandle.getGlfwHandle());
    }

    bool GLFWWindow::isVisible() const {
        return true;
    }
}
