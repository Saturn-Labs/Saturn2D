#include "Precompiled.hpp"
#include "Core/Window/GLFW/GLFWWindowFactory.hpp"

#include "Core/Logging/Log.hpp"

namespace Saturn {
    std::unique_ptr<IWindow> GLFWWindowFactory::createWindow(const WindowProperties &properties) {
        auto ptr = std::unique_ptr<IWindow>(new GLFWWindow(properties));
        Log::debug("[GLFWWindowFactory::createWindow] Created window {}.", toString(), ptr->toString());
        return ptr;
    }

    std::string GLFWWindowFactory::toString() const {
        return "GLFWWindowFactory";
    }
}
