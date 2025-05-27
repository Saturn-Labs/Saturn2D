#pragma once
#include "GLFW/glfw3.h"

namespace Saturn {
    class ScopedContext {
        GLFWwindow* _newContext = nullptr;
        GLFWwindow* _oldContext = nullptr;
        bool _oldWasNew = false;
    public:
        explicit ScopedContext(GLFWwindow* newContext) : _newContext(newContext) {
            _oldContext = glfwGetCurrentContext();
            _oldWasNew = _oldContext == _newContext;
            if (!_oldWasNew) {
                glfwMakeContextCurrent(_newContext);
            }
        }

        ~ScopedContext() {
            if (!_oldWasNew) {
                glfwMakeContextCurrent(_oldContext);
            }
        }

        ScopedContext(const ScopedContext&) = delete;
        ScopedContext& operator=(const ScopedContext&) = delete;
        ScopedContext(ScopedContext&& other) = delete;
        ScopedContext& operator=(ScopedContext&& other) = delete;
    };
}
