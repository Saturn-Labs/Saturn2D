#pragma once
#include <GLFW/glfw3.h>
#include "Core/Window/IWindow.hpp"
#include "Core/Window/WindowProperties.hpp"

namespace Saturn {
    class GLFWWindow final : public IWindow {
        friend class GLFWWindowFactory;
        NativeWindowHandle _windowHandle;
        WindowProperties _windowProperties;
        GraphicsContext _context;

        explicit GLFWWindow(const WindowProperties& properties);

    public:
        ~GLFWWindow() override;
        NativeWindowHandle getNativeHandle() const override;
        bool isValid() const override;
        void pollEvents() override;
        void swapBuffers() override;
        glm::vec2 getWindowSize() const override;
        glm::vec2 getWindowPosition() const override;
        std::string getWindowTitle() const override;
        float getWindowOpacity() const override;
        void setWindowSize(const glm::vec2 &size) override;
        void setWindowPosition(const glm::vec2 &position) override;
        void setWindowTitle(const std::string &title) override;
        void setWindowOpacity(float opacity) override;
        void setWindowIcon(uint32_t width, uint32_t height, unsigned char *pixels) override;
        void setInputMode(int mode, int value) override;
        bool isMaximized() const override;
        bool isIconified() const override;
        bool isFocused() const override;
        void maximize() override;
        void iconify() override;
        void focus() override;
        void restore() override;
        void setVSync(bool sync) override;
        const WindowProperties& getProperties() const override;
        bool shouldClose() const override;
        void setShouldClose(bool close) override;
        std::string toString() const override;
        const GraphicsContext& getContext() override;
        bool isVisible() override;

        // Window related events
        void onWindowResize(uint32_t width, uint32_t height);
        void onWindowClose();
        void onWindowRefresh();
        void onWindowFocus(bool focused);
        void onWindowIconified(bool iconified);
        void onWindowMaximized(bool maximized);
        void onFramebufferResize(uint32_t width, uint32_t height);
        void onContentScaleChange(float sx, float sy);
        void onWindowMove(int xp, int yp);

        // OpenGL related stuff
        void onOpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message) const;
        void makeContextCurrent();

    };
}
