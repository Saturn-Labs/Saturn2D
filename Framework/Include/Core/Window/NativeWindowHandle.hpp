#pragma once
#include <cstdint>

#include "GLFW/glfw3.h"

namespace Saturn {
    struct NativeWindowHandle {
    private:
        uintptr_t _handle;

    public:
        NativeWindowHandle(const uintptr_t handle) : _handle(handle) {}
        NativeWindowHandle(GLFWwindow* glfwWindow) : _handle(reinterpret_cast<uintptr_t>(glfwWindow)) {}
        uintptr_t getHandle() const { return _handle; }
        GLFWwindow* getGlfwHandle() const { return reinterpret_cast<GLFWwindow*>(_handle); }
    };
}
