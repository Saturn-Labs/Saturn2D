#pragma once
#include <cstdint>
#include <variant>
#include "GLFW/glfw3.h"

namespace Saturn {
    struct NativeWindowHandle {
        using GlfwHandle = GLFWwindow*;

    private:
        std::variant<std::monostate, GlfwHandle> _handle;

    public:
        NativeWindowHandle() = default;
        explicit NativeWindowHandle(GlfwHandle handle) :
            _handle(handle) {
        }

        bool isGlfw() const {
            return std::holds_alternative<GlfwHandle>(_handle);
        }

        GlfwHandle getGlfwHandle() const {
            if (!isGlfw())
                throw std::runtime_error("Trying to access NativeWindowHandle as GlfwHandle, but it isn't a GlfwHandle.");
            return std::get<GlfwHandle>(_handle);
        }

        uintptr_t getId() const {
            if (isGlfw()) {
                return reinterpret_cast<uintptr_t>(getGlfwHandle());
            }
            return 0;
        }
    };
}
