#include "Core/Logging/Log.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Saturn {
    bool Log::_initialized = false;
    std::shared_ptr<spdlog::logger> Log::_logger = nullptr;

    void Log::init(const std::string &name) {
        if (isInitialized())
            return;
        _initialized = true;
        if (_logger)
            spdlog::drop(_logger->name());
        _logger = spdlog::stdout_color_mt(name);
        _logger->set_level(spdlog::level::trace);
        _logger->set_pattern("%^[%T] %n: %v%$");
    }

    void Log::shutdown() {
        if (!isInitialized())
            return;
        _initialized = false;
        spdlog::drop(_logger->name());
        _logger.reset();
    }

    bool Log::isInitialized() {
        return _initialized;
    }
}
