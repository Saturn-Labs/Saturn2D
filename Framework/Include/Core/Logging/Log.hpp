#pragma once
#include <memory>

#include "spdlog/logger.h"

namespace Saturn {
    class Log {
        friend class Framework;
    private:
        static bool _initialized;
        static std::shared_ptr<spdlog::logger> _logger;

        static void init(const std::string& name);
        static void shutdown();

    public:
        static bool isInitialized();

        template<typename... Args>
        static void debug(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            if (!isInitialized())
                return;
            #ifdef DEBUG_BUILD
            _logger->trace(format, std::forward<Args>(args)...);
            #endif
        };

        template<typename... Args>
        static void trace(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            if (!isInitialized())
                return;
            _logger->trace(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void info(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            if (!isInitialized())
                return;
            _logger->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void warn(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            if (!isInitialized())
                return;
            _logger->warn(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void error(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            if (!isInitialized())
                return;
            _logger->error(format, std::forward<Args>(args)...);
        }
    };
}
