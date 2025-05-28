#pragma once
#include <memory>
#include <queue>
#include <unordered_map>

#include "Core/Window/IWindow.hpp"
#include "Core/Window/IWindowFactory.hpp"

namespace Saturn {
    class WindowManager {
        friend class Framework;
    private:
        std::unique_ptr<IWindowFactory> _windowFactory;
        std::unordered_map<uintptr_t, std::unique_ptr<IWindow>> _ownedWindows{};
        std::queue<std::unique_ptr<IWindow>> _windowsToDestroy{};


        explicit WindowManager(std::unique_ptr<IWindowFactory>&& factory);

    public:
        WindowManager() = delete;
        WindowManager(const WindowManager&) = delete;
        WindowManager(WindowManager&&) = delete;
        WindowManager& operator=(const WindowManager&) = delete;
        WindowManager& operator=(WindowManager&&) = delete;

        ~WindowManager() = default;
        IWindow& createWindow(const WindowProperties& properties);
        void updateWindows(const std::function<void(IWindow&)>& onRender);
        void destroyWindows();
        bool hasVisibleWindows() const;
    };
}
