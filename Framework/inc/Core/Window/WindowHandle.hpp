#pragma once
#include "Core/Common/Types.hpp"
#include "GLFW/glfw3.h"

namespace Saturn {
    enum class WindowHandleType {
        Unknown = -1,
        GLFW
    };

    class WindowHandle {
        using GLFWHandle = GLFWwindow*;
    private:
        WindowHandleType _handleType = WindowHandleType::Unknown;
        Multiple<std::monostate, GLFWHandle> _underlyingHandle = std::monostate{};
    public:
        explicit WindowHandle(GLFWHandle handle);

        WindowHandle() = default;
        WindowHandle(const WindowHandle& other);
        WindowHandle& operator=(const WindowHandle& other);
        WindowHandle(WindowHandle&& other) noexcept;
        WindowHandle& operator=(WindowHandle&& other) noexcept;
        ~WindowHandle();

        bool isValid() const;
        bool isOfType(WindowHandleType type) const;
        bool equals(const WindowHandle& other) const;

        GLFWHandle getGLFWHandle() const;
        Nullable<GLFWHandle> tryGetGLFWHandle() const;

        operator bool() const;
        bool operator==(const WindowHandle& other) const;
        bool operator!=(const WindowHandle& other) const;
    };
}
