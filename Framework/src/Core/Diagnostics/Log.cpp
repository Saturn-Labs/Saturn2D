#include "Core/Diagnostics/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Saturn {
    bool Log::_initialized = false;
    Ref<spdlog::logger> Log::_logger = nullptr;

    void Log::init(const String& name) {
        if (_initialized)
            return;
        _initialized = true;
        if (_logger)
            spdlog::drop(_logger->name());
        _logger = spdlog::stdout_color_mt(name);
        _logger->set_level(spdlog::level::trace);
        _logger->set_pattern("%^[%T] %n: %v%$");
    }

    void Log::shutdown() {
        if (!_initialized)
            return;
        _initialized = false;
        spdlog::drop(_logger->name());
        _logger.reset();
    }

    bool Log::isInitialized() {
        return _initialized;
    }
}
