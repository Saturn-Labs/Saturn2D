#pragma once
#include "Core/Framework.hpp"
#include "GLFW/glfw3.h"

namespace Saturn {
    class ScopedOpenGLContext {
        GLFWwindow* _newContext = nullptr;
        GLFWwindow* _oldContext = nullptr;
        bool _oldWasNew = false;
    public:
        explicit ScopedOpenGLContext(GLFWwindow* newContext) : _newContext(newContext) {
            if (!Framework::getInstance().hasGlfwContext())
                throw std::runtime_error("Scoped OpenGL context could not be created! (There is no GLFW context)");

            _oldContext = glfwGetCurrentContext();
            _oldWasNew = _oldContext == _newContext;
            if (!_oldWasNew) {
                glfwMakeContextCurrent(_newContext);
            }
        }

        ~ScopedOpenGLContext() {
            if (!_oldWasNew) {
                glfwMakeContextCurrent(_oldContext);
            }
        }

        ScopedOpenGLContext(const ScopedOpenGLContext&) = delete;
        ScopedOpenGLContext& operator=(const ScopedOpenGLContext&) = delete;
        ScopedOpenGLContext(ScopedOpenGLContext&& other) = delete;
        ScopedOpenGLContext& operator=(ScopedOpenGLContext&& other) = delete;
    };
}
