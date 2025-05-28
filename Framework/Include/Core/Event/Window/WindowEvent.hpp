#pragma once
#include "Core/Event/Event.hpp"

namespace Saturn {
    class IWindow;

    class WindowEvent : public Event {
        IWindow& _window;
    public:
        explicit WindowEvent(const EventType& type, IWindow& window) :
            Event(type),
            _window(window) {
        }

        ~WindowEvent() override = default;

        IWindow& getWindow() const {
            return _window;
        }
    };
}
