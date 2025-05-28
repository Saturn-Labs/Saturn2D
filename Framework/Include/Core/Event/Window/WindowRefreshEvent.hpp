#pragma once
#include "WindowEvent.hpp"

namespace Saturn {
    class IWindow;
    class WindowRefreshEvent final : public WindowEvent {
    public:
        explicit WindowRefreshEvent(IWindow& window) :
            WindowEvent(EventType::WindowRefresh, window) {
        }
    };
}
