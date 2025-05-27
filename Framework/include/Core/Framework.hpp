#pragma once
#include <memory>
#include <mutex>

namespace Saturn {
    class Framework {
    private:
        static std::unique_ptr<Framework> _instance;
        static std::once_flag _initFlag;

        Framework();
        static void initInstance();
    public:
        ~Framework();
        Framework(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework& operator=(Framework&&) = delete;
        static Framework& getInstance();
    };
}
