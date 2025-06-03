#include "Precompiled.hpp"
#include "Core/Application/Application.hpp"
#include "Core/Diagnostics/Log.hpp"

namespace Saturn {
    bool Application::_hasOneApplication = false;

    Application::Application(const String& name, const String& author) :
        _name(name),
        _author(author) {
        if (_hasOneApplication)
            throw std::logic_error("There is already one application instance, you can't create multiple applications.");
        _hasOneApplication = true;
        Log::init(name);
    }

    Application::~Application() {
        Log::shutdown();
        _hasOneApplication = false;
    }

    void Application::start() {
    }

    void Application::stop() {
    }
}
