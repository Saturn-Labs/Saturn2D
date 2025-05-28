#pragma once
#include "EventType.hpp"

namespace Saturn {
    class Event {
        friend class EventSystem;
        EventType _type;
    protected:
        explicit Event(const EventType& type);
    public:
        virtual ~Event() = default;
        EventType getType() const;
        std::string getTypeName() const;

        static std::string getEventTypeName(const EventType& type) {
            switch (type) {
                case EventType::WindowResize:
                    return "WindowResize";
                case EventType::WindowClose:
                    return "WindowClose";
                case EventType::WindowRefresh:
                    return "WindowRefresh";
                case EventType::WindowFocus:
                    return "WindowFocus";
                case EventType::WindowIconify:
                    return "WindowIconify";
                case EventType::WindowMaximize:
                    return "WindowMaximize";
                case EventType::FramebufferResize:
                    return "FramebufferResize";
                case EventType::ContentScaleChange:
                    return "ContentScaleChange";
                case EventType::WindowMove:
                    return "WindowMove";
                default:
                    return "UnknownEvent";
            }
        };
    };
}
