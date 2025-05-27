#include "Precompiled.hpp"
#include "Core/Window/GLFW/GLFWWindowFactory.hpp"

namespace Saturn {
    std::unique_ptr<IWindow> GLFWWindowFactory::createWindow(const WindowProperties &properties) {
        return std::unique_ptr<IWindow>(new GLFWWindow(properties));
    }
}
