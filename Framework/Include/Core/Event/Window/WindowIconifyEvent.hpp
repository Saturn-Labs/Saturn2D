#pragma once
#include "WindowEvent.hpp"

namespace Saturn {
    class IWindow;
    class WindowIconifyEvent final : public WindowEvent {
        bool _iconified;
    public:
        explicit WindowIconifyEvent(IWindow& window, bool iconified) :
            WindowEvent(EventType::WindowIconify, window),
            _iconified(iconified) {
        }

        bool isIconified() const {
            return _iconified;
        }
    };
}
