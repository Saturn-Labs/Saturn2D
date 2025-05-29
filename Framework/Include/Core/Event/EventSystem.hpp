#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "Event.hpp"

namespace Saturn {
    class EventSystem {
        friend class Framework;
    public:
        using EventList = std::vector<std::unique_ptr<Event>>;
        using EventListenerFn = bool(*)(const Event&);
        using EventListenerList = std::unordered_map<EventType, std::vector<EventListenerFn>>;

    private:
        EventList _events{};
        EventListenerList _listeners{};

        EventSystem();
        ~EventSystem();
        void dispatchEvents();
    public:
        EventSystem(const EventSystem&) = delete;
        EventSystem& operator=(const EventSystem&) = delete;
        EventSystem(EventSystem&&) = delete;
        EventSystem& operator=(EventSystem&&) = delete;

        const EventList& getEvents() const;
        const EventListenerList& getListeners() const;
        void addListener(const EventType& type, const EventListenerFn& listener);
        void removeListener(const EventType& type, const EventListenerFn& listener);

        template<typename TEvent, typename... Args>
        requires std::is_constructible_v<TEvent, Args&&...>
        TEvent& createEvent(Args&&... args) {
            auto ptr = std::unique_ptr<Event>(new TEvent(std::forward<Args>(args)...));
            _events.emplace_back(std::move(ptr));
            return *static_cast<TEvent*>(_events.back().get());
        }
    };
}
