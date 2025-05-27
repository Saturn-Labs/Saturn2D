#include <memory>

#include "Precompiled.hpp"
#include "Core/Framework.hpp"

#include "Core/Logging/Log.hpp"
#include "Core/Window/GLFW/GLFWWindowFactory.hpp"
#include "spdlog/spdlog.h"

namespace Saturn {
    std::unique_ptr<Framework> Framework::_instance;
    std::once_flag Framework::_initFlag;

    Framework::Framework() {
        Log::init("Saturn2D");
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");
        _windowManager.reset(new WindowManager(std::unique_ptr<GLFWWindowFactory>(new GLFWWindowFactory())));
    }

    Framework::~Framework() {
        glfwTerminate();
        Log::shutdown();
    }

    void Framework::initInstance() {
        _instance.reset(new Framework());
    }

    Framework& Framework::getInstance() {
        std::call_once(_initFlag, initInstance);
        return *_instance;
    }

    WindowManager& Framework::getWindowManager() const {
        return *_windowManager;
    }
}
