#pragma once
#include <memory>
#include <mutex>

#include "Window/IWindowFactory.hpp"
#include "Window/Management/WindowManager.hpp"

namespace Saturn {
    class Framework {
    private:
        static std::unique_ptr<Framework> _instance;
        static std::once_flag _initFlag;

        std::unique_ptr<WindowManager> _windowManager;

        Framework();
        static void initInstance();

    public:
        ~Framework();
        Framework(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework& operator=(Framework&&) = delete;
        static Framework& getInstance();
        [[nodiscard]] WindowManager& getWindowManager() const;
    };
}
