#pragma once
#include <functional>

#include "NativeWindowHandle.hpp"

namespace Saturn {
    class IWindow {
    protected:
        IWindow() = default;
    public:
        IWindow(const IWindow&) = delete;
        IWindow& operator=(const IWindow&) = delete;
        IWindow(IWindow&&) = delete;
        IWindow& operator=(IWindow&&) = delete;

        virtual ~IWindow() = default;
        [[nodiscard]] virtual NativeWindowHandle getNativeHandle() const = 0;
        [[nodiscard]] virtual bool isValid() = 0;
        virtual void pollEvents() = 0;
        virtual void swapBuffers() = 0;
        virtual void setContextCurrent() = 0;
        [[nodiscard]] virtual bool isVisible() const = 0;
    };
}
