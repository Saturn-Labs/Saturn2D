#pragma once
#include "GLFW/glfw3.h"

namespace Saturn {
    enum class ContextCreationAPI {
        NativeContext = GLFW_NATIVE_CONTEXT_API,
        EGLContext = GLFW_EGL_CONTEXT_API,
        OSMesaContext = GLFW_OSMESA_CONTEXT_API
    };
}
