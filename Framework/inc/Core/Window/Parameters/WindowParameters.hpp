#pragma once
#include "Core/Common/Types.hpp"

namespace Saturn {
    class WindowParameters {
    public:
        String title;
        u32 width;
        u32 height;

        virtual ~WindowParameters() = default;
    };
}
