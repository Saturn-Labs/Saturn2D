#include "Core/Event/Event.hpp"

namespace Saturn {
    Event::Event(const EventType& type) :
        _type(type) {
    }

    EventType Event::getType() const {
        return _type;
    }

    std::string Event::getTypeName() const {
        return getEventTypeName(getType());
    }
}
