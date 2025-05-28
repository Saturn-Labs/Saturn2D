#pragma once
#include "WindowEvent.hpp"

namespace Saturn {
    class IWindow;
    class WindowCloseEvent final : public WindowEvent {
    public:
        explicit WindowCloseEvent(IWindow& window) :
            WindowEvent(EventType::WindowClose, window) {
        }
    };
}
