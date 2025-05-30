#include "Core/Graphics/GraphicsContext.hpp"
#include "Core/Window/IWindow.hpp"

namespace Saturn {
    GraphicsContext::GraphicsContext(const std::function<void()>& makeCurrentFn, IWindow* window) :
        _makeCurrentFunction(makeCurrentFn),
        _window(window) {
    }

    void GraphicsContext::makeCurrent() const {
        _makeCurrentFunction();
    }

    IWindow* GraphicsContext::getWindow() const {
        return _window;
    }
}
