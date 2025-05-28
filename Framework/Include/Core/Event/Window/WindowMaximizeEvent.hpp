#pragma once
#include "WindowEvent.hpp"

namespace Saturn {
    class IWindow;
    class WindowMaximizeEvent final : public WindowEvent {
        bool _maximized;
    public:
        explicit WindowMaximizeEvent(IWindow& window, bool maximized) :
            WindowEvent(EventType::WindowMaximize, window),
            _maximized(maximized) {
        }

        bool isMaximized() const {
            return _maximized;
        }
    };
}
