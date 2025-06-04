#include "Core/Window/WindowHandle.hpp"

#include <stdexcept>

namespace Saturn {
    WindowHandle::WindowHandle(GLFWHandle handle) :
        _handleType(WindowHandleType::GLFW),
        _underlyingHandle(handle) {
    }

    WindowHandle::WindowHandle(const WindowHandle& other) :
        _handleType(other._handleType),
        _underlyingHandle(other._underlyingHandle) {
    }

    WindowHandle& WindowHandle::operator=(const WindowHandle& other) {
        if (this != &other) {
            _handleType = other._handleType;
            _underlyingHandle = other._underlyingHandle;
        }
        return *this;
    }

    WindowHandle::WindowHandle(WindowHandle&& other) noexcept :
        _handleType(std::exchange(other._handleType, WindowHandleType::Unknown)),
        _underlyingHandle(std::exchange(other._underlyingHandle, std::monostate{})) {
    }

    WindowHandle& WindowHandle::operator=(WindowHandle&& other) noexcept {
        if (this != &other) {
            _handleType = std::exchange(other._handleType, WindowHandleType::Unknown);
            _underlyingHandle = std::exchange(other._underlyingHandle, std::monostate{});
        }
        return *this;
    }

    WindowHandle::~WindowHandle() = default;

    bool WindowHandle::isValid() const {
        return _handleType != WindowHandleType::Unknown && !_underlyingHandle.valueless_by_exception() && _underlyingHandle.index() != 0;
    }

    bool WindowHandle::isOfType(WindowHandleType type) const {
        return _handleType == type;
    }

    bool WindowHandle::equals(const WindowHandle& other) const {
        if (!isOfType(other._handleType))
            return false;
        return _underlyingHandle == other._underlyingHandle;
    }

    WindowHandle::GLFWHandle WindowHandle::getGLFWHandle() const {
        if (!isOfType(WindowHandleType::GLFW))
            throw std::runtime_error("Trying to get a GLFW window handle on a invalid or non-GLFW window handle!");
        return std::get<GLFWHandle>(_underlyingHandle);
    }

    Nullable<WindowHandle::GLFWHandle> WindowHandle::tryGetGLFWHandle() const {
        if (!isOfType(WindowHandleType::GLFW))
            return std::nullopt;
        return std::get<GLFWHandle>(_underlyingHandle);
    }

    WindowHandle::operator bool() const {
        if (isOfType(WindowHandleType::GLFW)) {
            return isValid() && getGLFWHandle() != nullptr;
        }
        return false;
    }

    bool WindowHandle::operator==(const WindowHandle& other) const {
        return equals(other);
    }

    bool WindowHandle::operator!=(const WindowHandle& other) const {
        return !equals(other);
    }
}
