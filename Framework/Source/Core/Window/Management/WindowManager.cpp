#include "Core/Window/Management/WindowManager.hpp"

#include <ranges>

namespace Saturn {
    WindowManager::WindowManager(std::unique_ptr<IWindowFactory>&& factory) :
        _windowFactory(std::move(factory))
    {
    }

    IWindow& WindowManager::createWindow(const WindowProperties& properties) {
        auto window = _windowFactory->createWindow(properties);
        auto id = window->getNativeHandle().getHandle();
        _ownedWindows[id] = std::move(window);
        return *_ownedWindows[id];
    }

    void WindowManager::renderWindows(const std::function<void(IWindow&)>& onRender) {
        for (auto it = _ownedWindows.begin(); it != _ownedWindows.end(); ) {
            auto& window = it->second;

            if (!window->isValid()) {
                it = _ownedWindows.erase(it);
                continue;
            }

            window->setContextCurrent();
            window->pollEvents();
            onRender(*window);
            window->swapBuffers();
            ++it;
        }
    }

    bool WindowManager::hasVisibleWindows() const {
        for (const auto& window: _ownedWindows | std::views::values) {
            if (window->isValid() && window->isVisible()) {
                return true;
            }
        }
        return false;
    }
}
