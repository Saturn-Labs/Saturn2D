#include "Precompiled.hpp"
#include "Core/Window/GLFW/GLFWWindow.hpp"

#include <stdexcept>

#include "Core/Window/GLFW/ScopedContext.hpp"
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

        _windowHandle = NativeWindowHandle(glfwCreateWindow(
            static_cast<int>(properties.width),
            static_cast<int>(properties.height),
            properties.title.c_str(),
            monitor,
            share
        ));

        if (!_windowHandle.getGlfwHandle()) {
            throw std::runtime_error("Failed to create GLFW window!");
        }

        if (modifiedHints)
            glfwDefaultWindowHints();

        ScopedContext ctx(_windowHandle.getGlfwHandle());
        setVSync(properties.shouldVSync);
    }

    GLFWWindow::~GLFWWindow() {
        glfwDestroyWindow(_windowHandle.getGlfwHandle());
    }

    NativeWindowHandle GLFWWindow::getNativeHandle() const {
        return _windowHandle;
    }

    bool GLFWWindow::isValid() const {
        return _windowHandle.getGlfwHandle() && !glfwWindowShouldClose(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::pollEvents() {
        if (!isValid())
            return;
        ScopedContext ctx(_windowHandle.getGlfwHandle());
        glfwPollEvents();
    }

    void GLFWWindow::swapBuffers() {
        if (!isValid())
            return;
        glfwSwapBuffers(_windowHandle.getGlfwHandle());
    }

    glm::vec2 GLFWWindow::getWindowSize() const {
        if (!isValid())
            return glm::vec2(0.0f, 0.0f);
        int width, height;
        glfwGetWindowSize(_windowHandle.getGlfwHandle(), &width, &height);
        return glm::vec2(width, height);
    }

    glm::vec2 GLFWWindow::getWindowPosition() const {
        if (!isValid())
            return glm::vec2(0.0f, 0.0f);
        int x, y;
        glfwGetWindowPos(_windowHandle.getGlfwHandle(), &x, &y);
        return glm::vec2(x, y);
    }

    std::string GLFWWindow::getWindowTitle() const {
        if (!isValid())
            return "";
        return glfwGetWindowTitle(_windowHandle.getGlfwHandle());
    }

    float GLFWWindow::getWindowOpacity() const {
        if (!isValid())
            return 0;
        return glfwGetWindowOpacity(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::setWindowSize(const glm::vec2 &size) {
        if (!isValid())
            return;
        glfwSetWindowSize(_windowHandle.getGlfwHandle(), static_cast<int>(size.x), static_cast<int>(size.y));
    }

    void GLFWWindow::setWindowPosition(const glm::vec2 &position) {
        if (!isValid())
            return;
        glfwSetWindowPos(_windowHandle.getGlfwHandle(), static_cast<int>(position.x), static_cast<int>(position.y));
    }

    void GLFWWindow::setWindowTitle(const std::string &title) {
        if (!isValid())
            return;
        glfwSetWindowTitle(_windowHandle.getGlfwHandle(), title.c_str());
    }

    void GLFWWindow::setWindowOpacity(float opacity) {
        if (!isValid())
            return;
        glfwSetWindowOpacity(_windowHandle.getGlfwHandle(), opacity);
    }

    void GLFWWindow::setWindowIcon(uint32_t width, uint32_t height, unsigned char *pixels) {
        if (!isValid())
            return;
        const GLFWimage image {
            .width = static_cast<int>(width),
            .height = static_cast<int>(height),
            .pixels = pixels
        };
        glfwSetWindowIcon(_windowHandle.getGlfwHandle(), 1, &image);
    }

    void GLFWWindow::setInputMode(int mode, int value) {
        if (!isValid())
            return;
        glfwSetInputMode(_windowHandle.getGlfwHandle(), mode, value);
    }

    bool GLFWWindow::isMaximized() const {
        if (!isValid())
            return false;
        return glfwGetWindowAttrib(_windowHandle.getGlfwHandle(), GLFW_MAXIMIZED);
    }

    bool GLFWWindow::isIconified() const {
        if (!isValid())
            return false;
        return glfwGetWindowAttrib(_windowHandle.getGlfwHandle(), GLFW_ICONIFIED);
    }

    bool GLFWWindow::isFocused() const {
        if (!isValid())
            return false;
        return glfwGetWindowAttrib(_windowHandle.getGlfwHandle(), GLFW_FOCUSED);
    }

    void GLFWWindow::maximize() {
        if (!isValid())
            return;
        glfwMaximizeWindow(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::iconify() {
        if (!isValid())
            return;
        glfwIconifyWindow(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::focus() {
        if (!isValid())
            return;
        glfwFocusWindow(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::restore() {
        if (!isValid())
            return;
        glfwRestoreWindow(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::setVSync(bool sync) {
        if (!isValid())
            return;
        ScopedContext ctx(_windowHandle.getGlfwHandle());
        glfwSwapInterval(sync ? 1 : 0);
    }
}
