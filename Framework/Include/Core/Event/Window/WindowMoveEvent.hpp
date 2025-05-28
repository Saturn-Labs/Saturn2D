#pragma once
#include "WindowEvent.hpp"
#include "Core/Event/Event.hpp"
#include "glm/vec2.hpp"

namespace Saturn {
    class WindowMoveEvent final : public WindowEvent {
        int _xPos, _yPos;
    public:
        explicit WindowMoveEvent(IWindow& window, int xPos, int yPos) :
            WindowEvent(EventType::WindowMove, window),
            _xPos(xPos),
            _yPos(yPos) {
        }

        ~WindowMoveEvent() override = default;

        int getXPos() const {
            return _xPos;
        }

        int getYPos() const {
            return _yPos;
        }

        glm::vec2 getPosition() const {
            return glm::vec2(_xPos, _yPos);
        }
    };
}
