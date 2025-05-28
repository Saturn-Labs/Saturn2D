#include "Precompiled.hpp"
#include "Core/Window/Management/WindowManager.hpp"

#include <ranges>

#include "Core/Logging/Log.hpp"
#include "Core/Window/GLFW/ScopedContext.hpp"

namespace Saturn {
    WindowManager::WindowManager(std::unique_ptr<IWindowFactory>&& factory) :
        _windowFactory(std::move(factory)) {
        Log::debug("Creating new WindowManager with factory '{}'.", _windowFactory->toString());
    }

    IWindow& WindowManager::createWindow(const WindowProperties& properties) {
        auto window = _windowFactory->createWindow(properties);
        const auto id = window->getNativeHandle().getId();
        _ownedWindows[id] = std::move(window);
        return *_ownedWindows[id];
    }

    void WindowManager::updateWindows(const std::function<void(IWindow&)>& onRender) {
        for (auto it = _ownedWindows.begin(); it != _ownedWindows.end(); ) {
            auto& window = it->second;
            if (window->isValid() && !window->shouldClose()) {
                ScopedContext ctx(window->getNativeHandle().getGlfwHandle());
                window->pollEvents();
                onRender(*window);
                window->swapBuffers();
                ++it;
            }
            else {
                _windowsToDestroy.push(std::move(window));
                it = _ownedWindows.erase(it);
            }
        }
    }

    void WindowManager::destroyWindows() {
        while (!_windowsToDestroy.empty()) {
            _windowsToDestroy.pop();
        }
    }

    bool WindowManager::hasVisibleWindows() const {
        for (const auto& window: _ownedWindows | std::views::values) {
            if (window->isValid()) {
                return true;
            }
        }
        return false;
    }
}
