#include "Core/Event/EventSystem.hpp"

#include "Core/Logging/Log.hpp"

namespace Saturn {
    EventSystem::EventSystem() = default;

    void EventSystem::dispatchEvents() {
        for (const auto& e : _events) {
            Log::debug("[EventSystem::dispatchEvents] Dispatched event '{}'.", e->getTypeName());
            if (!_listeners.contains(e->getType()))
                continue;
            const auto& listeners = _listeners[e->getType()];
            for (const auto& listener : listeners) {
                if (listener(*e))
                    break;
            }
        }
        _events.clear();
    }

    EventSystem::~EventSystem() =default;

    const EventSystem::EventList& EventSystem::getEvents() const {
        return _events;
    }

    const EventSystem::EventListenerList& EventSystem::getListeners() const {
        return _listeners;
    }

    void EventSystem::addListener(const EventType& type, const EventListenerFn& listener) {
        if (!_listeners.contains(type)) {
            _listeners[type] = std::vector<EventListenerFn>();
        }
        _listeners[type].push_back(listener);
    }

    void EventSystem::removeListener(const EventType& type, const EventListenerFn& listener) {
        if (!_listeners.contains(type))
            return;
        auto& listeners = _listeners[type];
        const auto it = std::ranges::find(listeners, listener);
        if (it == listeners.end())
            return;
        listeners.erase(it);
    }
}
