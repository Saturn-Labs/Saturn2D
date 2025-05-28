#pragma once
#include <memory>

#include "IWindow.hpp"
#include "WindowProperties.hpp"
#include "Core/Types/Object.hpp"

namespace Saturn {
    class IWindowFactory :
        public Object {
    public:
        ~IWindowFactory() override = default;
        virtual std::unique_ptr<IWindow> createWindow(const WindowProperties& properties) = 0;
    };
}
