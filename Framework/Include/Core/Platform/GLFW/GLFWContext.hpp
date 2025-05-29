#pragma once

namespace Saturn {
    class GLFWContext {
        friend class Framework;

        GLFWContext();
        ~GLFWContext();
    public:
        GLFWContext(const GLFWContext&) = delete;
        GLFWContext& operator=(const GLFWContext&) = delete;
        GLFWContext(GLFWContext&&) = delete;
        GLFWContext& operator=(GLFWContext&&) = delete;
    };
}