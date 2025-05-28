#pragma once
#include "WindowEvent.hpp"
#include "Core/Event/Event.hpp"

namespace Saturn {
    class WindowResizeEvent final : public WindowEvent {
        uint32_t _width, _height;
    public:
        explicit WindowResizeEvent(IWindow& window, uint32_t width, uint32_t height) :
            WindowEvent(EventType::WindowResize, window),
            _width(width),
            _height(height) {
        }

        ~WindowResizeEvent() override = default;

        uint32_t getWidth() const {
            return _width;
        }

        uint32_t getHeight() const {
            return _height;
        }

        glm::vec2 getSize() const {
            return glm::vec2(_width, _height);
        }
    };
}
