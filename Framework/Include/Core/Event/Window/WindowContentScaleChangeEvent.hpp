#pragma once
#include <cstdint>

#include "WindowEvent.hpp"
#include "glm/vec2.hpp"

namespace Saturn {
    class IWindow;
    class WindowContentScaleChangeEvent final : public WindowEvent {
        uint32_t _scaleX, _scaleY;
    public:
        explicit WindowContentScaleChangeEvent(IWindow& window, uint32_t scaleX, uint32_t scaleY) :
            WindowEvent(EventType::ContentScaleChange, window),
            _scaleX(scaleX),
            _scaleY(scaleY) {
        }

        ~WindowContentScaleChangeEvent() override = default;

        uint32_t getScaleX() const {
            return _scaleX;
        }

        uint32_t getScaleY() const {
            return _scaleY;
        }

        glm::vec2 getScale() const {
            return glm::vec2(_scaleX, _scaleY);
        }
    };
}
