#include <pch.hpp>
#include "Core/Framework.hpp"

namespace Saturn {
    std::unique_ptr<Framework> Framework::_instance;
    std::once_flag Framework::_initFlag;

    Framework::Framework() {
    }

    Framework::~Framework() {
    }

    void Framework::initInstance() {
        _instance.reset(new Framework());
    }

    Framework& Framework::getInstance() {
        // This ensures that initInstance is called once and it's thread-safe
        std::call_once(_initFlag, initInstance);
        return *_instance;
    }
}
