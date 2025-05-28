#pragma once
#include "WindowEvent.hpp"

namespace Saturn {
    class IWindow;
    class WindowFocusEvent final : public WindowEvent {
        bool _focused;
    public:
        explicit WindowFocusEvent(IWindow& window, bool focused) :
            WindowEvent(EventType::WindowFocus, window),
            _focused(focused) {
        }

        bool isFocused() const {
            return _focused;
        }
    };
}
