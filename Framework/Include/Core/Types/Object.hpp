#pragma once
#include <string>

namespace Saturn {
    class Object {
    public:
        virtual ~Object() = default;
        [[nodiscard]] virtual std::string toString() const = 0;
    };
}
