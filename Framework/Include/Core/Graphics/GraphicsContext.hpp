#pragma once
#include <functional>

namespace Saturn {
    class IWindow;
    class GraphicsContext {
        std::function<void()> _makeCurrentFunction;
        IWindow* _window;
    public:
        explicit GraphicsContext(const std::function<void()>& makeCurrentFn, IWindow* window);
        ~GraphicsContext() = default;
        void makeCurrent() const;
        IWindow* getWindow() const;
    };
}
