#pragma once
#include <memory>

#include "IWindow.hpp"
#include "WindowProperties.hpp"

namespace Saturn {
    class IWindowFactory {
    public:
        virtual ~IWindowFactory() = default;
        virtual std::unique_ptr<IWindow> createWindow(const WindowProperties& properties) = 0;
    };
}
