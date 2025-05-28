#pragma once

namespace Saturn {
    enum class EventType {
        Unknown = -1,
        WindowResize,
        WindowClose,
        WindowRefresh,
        WindowFocus,
        WindowIconify,
        WindowMaximize,
        FramebufferResize,
        ContentScaleChange,
        WindowMove
    };
}