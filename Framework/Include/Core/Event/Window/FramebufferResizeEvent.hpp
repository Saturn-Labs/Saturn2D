#pragma once
#include <cstdint>

#include "WindowEvent.hpp"
#include "glm/vec2.hpp"

namespace Saturn {
    class IWindow;
    class FramebufferResizeEvent final : public WindowEvent {
        uint32_t _width, _height;
    public:
        explicit FramebufferResizeEvent(IWindow& window, uint32_t width, uint32_t height) :
            WindowEvent(EventType::FramebufferResize, window),
            _width(width),
            _height(height) {
        }

        ~FramebufferResizeEvent() override = default;

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
