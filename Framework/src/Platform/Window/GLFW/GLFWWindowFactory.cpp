#include "Platform/Window/GLFW/GLFWWindowFactory.hpp"

#include <stdexcept>

#include "Platform/Window/GLFW/GLFWWindow.hpp"

namespace Saturn::Platform::GLFW {
    Unique<AbstractWindow> GLFWWindowFactory::createWindow(const WindowParameters& parameters) {
        auto* windowParameters = dynamic_cast<const GLFWWindowParameters*>(&parameters);
        if (!windowParameters)
            throw std::invalid_argument("Parameters must be GLFWWindowParameters");
        return Unique<GLFWWindow>(new GLFWWindow(*windowParameters));
    }
}
