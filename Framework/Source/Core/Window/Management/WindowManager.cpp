#include "Precompiled.hpp"
#include "Core/Window/Management/WindowManager.hpp"

#include <ranges>

#include "Core/Window/GLFW/ScopedContext.hpp"

namespace Saturn {
    WindowManager::WindowManager(std::unique_ptr<IWindowFactory>&& factory) :
        _windowFactory(std::move(factory))
    {
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
            if (!window->isValid()) {
                it = _ownedWindows.erase(it);
                continue;
            }

            ScopedContext ctx(window->getNativeHandle().getGlfwHandle());
            window->pollEvents();
            onRender(*window);
            window->swapBuffers();
            ++it;
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
