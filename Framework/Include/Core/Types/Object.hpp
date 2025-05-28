#pragma once
#include <string>

namespace Saturn {
    class Object {
    public:
        virtual ~Object() = default;
        virtual std::string toString() const = 0;
    };
}
