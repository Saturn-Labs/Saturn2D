#pragma once
#include <cstdint>
#include <string>

namespace Saturn {
    struct WindowProperties {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool shouldVSync = true;
        virtual ~WindowProperties() = default;
    };
}