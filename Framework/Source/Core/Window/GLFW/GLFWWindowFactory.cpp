#include "Precompiled.hpp"
#include "Core/Window/GLFW/GLFWWindowFactory.hpp"

#include "Core/Framework.hpp"
#include "Core/Logging/Log.hpp"
#include "Core/Window/GLFW/ScopedOpenGLContext.hpp"

namespace Saturn {
    GLFWWindowFactory::GLFWWindowFactory() = default;
    std::unique_ptr<IWindow> GLFWWindowFactory::createWindow(const WindowProperties &properties) {
        auto ptr = std::unique_ptr<IWindow>(new GLFWWindow(properties));
        {
            ScopedOpenGLContext ctx(ptr->getNativeHandle().getGlfwHandle());
            Log::debug("[GLFWWindowFactory::createWindow] Created window {} with 'OpenGL {}'.", ptr->toString(), reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        }
        return ptr;
    }

    std::string GLFWWindowFactory::toString() const {
        return "GLFWWindowFactory";
    }
}
