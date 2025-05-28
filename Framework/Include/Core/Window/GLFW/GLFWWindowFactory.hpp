#pragma once
#include "GLFWWindow.hpp"
#include "Core/Window/IWindowFactory.hpp"

namespace Saturn {
    class GLFWWindowFactory final : public IWindowFactory {
        friend class Framework;
    private:
        GLFWWindowFactory() = default;

    public:
        std::unique_ptr<IWindow> createWindow(const WindowProperties &properties) override;
        std::string toString() const override;
    };
}
