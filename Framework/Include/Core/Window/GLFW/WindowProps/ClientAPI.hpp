﻿#pragma once
#include "GLFW/glfw3.h"

namespace Saturn {
    enum class ClientAPI {
        None = GLFW_NO_API,
        OpenGL = GLFW_OPENGL_API,
        OpenGLES = GLFW_OPENGL_ES_API
    };
}
