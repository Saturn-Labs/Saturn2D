#pragma once
#include <GLFW/glfw3.h>
#include "Core/Window/IWindow.hpp"
#include "Core/Window/WindowProperties.hpp"

namespace Saturn {
    class GLFWWindow final : public IWindow {
        friend class GLFWWindowFactory;
    private:
        NativeWindowHandle _windowHandle;

        explicit GLFWWindow(const WindowProperties& properties);

    public:
        ~GLFWWindow() override;
        [[nodiscard]] NativeWindowHandle getNativeHandle() const override;
        [[nodiscard]] bool isValid() override;
        void pollEvents() override;
        void swapBuffers() override;
        void setContextCurrent() override;

        [[nodiscard]] bool isVisible() const override;
    };
}
