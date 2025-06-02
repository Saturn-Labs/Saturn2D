#pragma once
#include "Core/Common/Types.hpp"
#include "spdlog/spdlog.h"

namespace Saturn {
    class Log {
        static bool _initialized;
        static Ref<spdlog::logger> _logger;

    public:
        Log() = delete;

        static void init(const String& name);
        static void shutdown();
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
