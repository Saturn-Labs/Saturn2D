#pragma once
#include "Core/Window/AbstractWindow.hpp"
#include "Parameters/GLFWWindowParameters.hpp"

namespace Saturn::Platform::GLFW {
    class GLFWWindow final : public AbstractWindow {
        friend class GLFWWindowFactory;

        explicit GLFWWindow(const GLFWWindowParameters& parameters);
    public:

    };
}
