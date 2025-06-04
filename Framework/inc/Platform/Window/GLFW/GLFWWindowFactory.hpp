#pragma once
#include "Core/Window/IWindowFactory.hpp"

namespace Saturn::Platform::GLFW {
    class GLFWWindowFactory final : public IWindowFactory {
    public:
        Unique<AbstractWindow> createWindow(const WindowParameters& parameters) override;
    };
}