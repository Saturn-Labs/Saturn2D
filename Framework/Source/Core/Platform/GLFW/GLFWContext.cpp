#include "Core/Platform/GLFW/GLFWContext.hpp"

#include <stdexcept>
#include <GLFW/glfw3.h>

#include "Core/Logging/Log.hpp"

namespace Saturn {
    GLFWContext::GLFWContext() {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");
        Log::debug("GLFW {} was initialized.", glfwGetVersionString());
    }

    GLFWContext::~GLFWContext() {
        glfwTerminate();
        Log::debug("GLFW was terminated.");
    }
}
