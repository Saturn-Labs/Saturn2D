#pragma once
#include <functional>
#include <glm/glm.hpp>
#include "NativeWindowHandle.hpp"
#include "WindowProperties.hpp"
#include "Core/Graphics/GraphicsContext.hpp"
#include "Core/Types/Object.hpp"

namespace Saturn {
    class IWindow :
        public Object {
    protected:
        IWindow() = default;
    public:
        IWindow(const IWindow&) = delete;
        IWindow& operator=(const IWindow&) = delete;
        IWindow(IWindow&&) = delete;
        IWindow& operator=(IWindow&&) = delete;

        ~IWindow() override = default;
        virtual NativeWindowHandle getNativeHandle() const = 0;
        virtual bool isValid() const = 0;
        virtual void pollEvents() = 0;
        virtual void swapBuffers() = 0;
        virtual glm::vec2 getWindowSize() const = 0;
        virtual glm::vec2 getWindowPosition() const = 0;
        virtual std::string getWindowTitle() const = 0;
        virtual float getWindowOpacity() const = 0;
        virtual void setWindowSize(const glm::vec2& size) = 0;
        virtual void setWindowPosition(const glm::vec2& position) = 0;
        virtual void setWindowTitle(const std::string& title) = 0;
        virtual void setWindowOpacity(float opacity) = 0;
        virtual void setWindowIcon(uint32_t width, uint32_t height, unsigned char* pixels) = 0;
        virtual void setInputMode(int mode, int value) = 0;
        virtual bool isMaximized() const = 0;
        virtual bool isIconified() const = 0;
        virtual bool isFocused() const = 0;
        virtual void maximize() = 0;
        virtual void iconify() = 0;
        virtual void focus() = 0;
        virtual void restore() = 0;
        virtual void setVSync(bool sync) = 0;
        virtual const WindowProperties& getProperties() const = 0;
        virtual bool shouldClose() const = 0;
        virtual void setShouldClose(bool close) = 0;
        virtual const GraphicsContext& getContext() = 0;
        virtual bool isVisible() = 0;
    };
}
