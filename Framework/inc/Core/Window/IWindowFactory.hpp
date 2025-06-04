#pragma once
#include "AbstractWindow.hpp"
#include "Core/Common/Types.hpp"
#include "Parameters/WindowParameters.hpp"

namespace Saturn {
    class IWindowFactory {
    protected:
        IWindowFactory() = default;

    public:
        virtual ~IWindowFactory() = default;
        virtual Unique<AbstractWindow> createWindow(const WindowParameters& parameters) = 0;
    };
}
