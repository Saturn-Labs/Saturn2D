#pragma once
#include "WindowHandle.hpp"
#include "Parameters/WindowParameters.hpp"

namespace Saturn {
    class IWindow {
    protected:
        IWindow() = default;
    public:
        virtual ~IWindow() = default;
        virtual WindowHandle getHandle() const = 0;
        
    };
}
