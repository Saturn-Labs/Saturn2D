#include "Precompiled.hpp"
#include "Core/Window/GLFW/GLFWWindow.hpp"

#include <stdexcept>

#include "Core/Framework.hpp"
#include "Core/Event/Window/FramebufferResizeEvent.hpp"
#include "Core/Event/Window/WindowCloseEvent.hpp"
#include "Core/Event/Window/WindowContentScaleChangeEvent.hpp"
#include "Core/Event/Window/WindowFocusEvent.hpp"
#include "Core/Event/Window/WindowIconifyEvent.hpp"
#include "Core/Event/Window/WindowMaximizeEvent.hpp"
#include "Core/Event/Window/WindowMoveEvent.hpp"
#include "Core/Event/Window/WindowRefreshEvent.hpp"
#include "Core/Event/Window/WindowResizeEvent.hpp"
#include "Core/Logging/Log.hpp"
#include "Core/Window/GLFW/ScopedOpenGLContext.hpp"
#include "Core/Window/GLFW/WindowProps/GLFWWindowProperties.hpp"

namespace Saturn {
    GLFWWindow::GLFWWindow(const WindowProperties& properties) :
        IWindow(),
        _windowHandle(nullptr),
        _windowProperties(properties)
    {
        if (!Framework::getInstance().hasGlfwContext())
            throw std::runtime_error("GLFW window could not be created! (There is no GLFW context)");

        GLFWmonitor* monitor = nullptr;
        GLFWwindow* share = nullptr;
        bool modifiedHints = false;
        bool debugContext = false;
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
            debugContext = glfwProps->debugContext;
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

        ScopedOpenGLContext ctx(_windowHandle.getGlfwHandle());
        if (!_windowHandle.getGlfwHandle())
            throw std::runtime_error("Failed to create GLFW window!");
        if (!gladLoadGL(glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        if (modifiedHints)
            glfwDefaultWindowHints();

        // Sets the OpenGL debug message callback
        if (debugContext) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
                auto* window = static_cast<const GLFWWindow*>(userParam);
                window->onOpenGLDebugMessage(source, type, id, severity, length, message);
            }, this);
        }

        // Sets the user pointer to this GLFWWindow
        glfwSetWindowUserPointer(_windowHandle.getGlfwHandle(), this);

        // Sets the resize callback
        glfwSetWindowSizeCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, int width, int height) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowResize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
        });

        // Sets the close callback
        glfwSetWindowCloseCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowClose();
        });

        // Sets the refresh callback
        glfwSetWindowRefreshCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowRefresh();
        });

        // Sets the focus callback
        glfwSetWindowFocusCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, int focused) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowFocus(focused);
        });

        // Sets the iconify callback
        glfwSetWindowIconifyCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, int iconified) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowIconified(iconified);
        });

        // Sets the maximize callback
        glfwSetWindowMaximizeCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, int maximized) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowMaximized(maximized);
        });

        // Sets the framebuffer resize callback
        glfwSetFramebufferSizeCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, int width, int height) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onFramebufferResize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
        });

        // Sets the content scale callback
        glfwSetWindowContentScaleCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, float xScale, float yScale) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onContentScaleChange(xScale, yScale);
        });

        // Sets the move callback
        glfwSetWindowPosCallback(_windowHandle.getGlfwHandle(), [](GLFWwindow* win, int xPos, int yPos) {
            GLFWWindow& window = *static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win));
            window.onWindowMove(xPos, yPos);
        });
        setVSync(properties.shouldVSync);
    }

    GLFWWindow::~GLFWWindow() {
        glfwDestroyWindow(_windowHandle.getGlfwHandle());
    }

    NativeWindowHandle GLFWWindow::getNativeHandle() const {
        return _windowHandle;
    }

    bool GLFWWindow::isValid() const {
        return _windowHandle.getGlfwHandle();
    }

    void GLFWWindow::pollEvents() {
        if (!isValid())
            return;
        ScopedOpenGLContext ctx(_windowHandle.getGlfwHandle());
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
        _windowProperties.width = static_cast<int>(size.x);
        _windowProperties.height = static_cast<int>(size.y);
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
        _windowProperties.title = title;
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
        ScopedOpenGLContext ctx(_windowHandle.getGlfwHandle());
        glfwSwapInterval(sync ? 1 : 0);
    }

    const WindowProperties& GLFWWindow::getProperties() const {
        return _windowProperties;
    }

    bool GLFWWindow::shouldClose() const {
        return glfwWindowShouldClose(_windowHandle.getGlfwHandle());
    }

    void GLFWWindow::setShouldClose(bool close) {
        if (!isValid())
            return;
        glfwSetWindowShouldClose(_windowHandle.getGlfwHandle(), close);
    }

    std::string GLFWWindow::toString() const {
        auto size = getWindowSize();
        return std::format("[GLFWWindow, '{}', {}x{}]", getWindowTitle(), size.x, size.y);
    }

    void GLFWWindow::onWindowResize(uint32_t width, uint32_t height) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowResizeEvent>(*this, width, height);
    }

    void GLFWWindow::onWindowClose() {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowCloseEvent>(*this);
    }

    void GLFWWindow::onWindowRefresh() {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowRefreshEvent>(*this);
    }

    void GLFWWindow::onWindowFocus(bool focused) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowFocusEvent>(*this, focused);
    }

    void GLFWWindow::onWindowIconified(bool iconified) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowIconifyEvent>(*this, iconified);
    }

    void GLFWWindow::onWindowMaximized(bool maximized) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowMaximizeEvent>(*this, maximized);
    }

    void GLFWWindow::onFramebufferResize(uint32_t width, uint32_t height) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<FramebufferResizeEvent>(*this, width, height);
    }

    void GLFWWindow::onContentScaleChange(float sx, float sy) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowContentScaleChangeEvent>(*this, sx, sy);
    }

    void GLFWWindow::onWindowMove(int xp, int yp) {
        const auto& framework = Framework::getInstance();
        framework.getEventSystem().createEvent<WindowMoveEvent>(*this, xp, yp);
    }

    void GLFWWindow::onOpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message) const {
        Log::debug("OpenGL debug message: {}", message);
    }
}
