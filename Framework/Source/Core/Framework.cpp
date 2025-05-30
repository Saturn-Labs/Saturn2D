#include "Precompiled.hpp"
#include <memory>
#include "Core/Framework.hpp"

#include "Core/Types.hpp"
#include "Core/Event/EventSystem.hpp"
#include "Core/Event/Window/WindowResizeEvent.hpp"
#include "Core/Graphics/Resource/OpenGL/OpenGLResourceFactory.hpp"
#include "Core/Logging/Log.hpp"
#include "Core/Window/GLFW/GLFWWindowFactory.hpp"
#include "Core/Window/GLFW/WindowProps/GLFWWindowProperties.hpp"
#include "spdlog/spdlog.h"

namespace Saturn {
    std::unique_ptr<Framework> Framework::_instance;
    std::once_flag Framework::_initFlag;

    Framework::Framework() {
        Log::init("Saturn2D");
        _glfwContext = new GLFWContext();
        _windowManager = new WindowManager(std::unique_ptr<GLFWWindowFactory>(new GLFWWindowFactory()));
        _eventSystem = new EventSystem();
    }

    Framework::~Framework() {
        delete _resourceManager;
        delete _eventSystem;
        delete _windowManager;
        delete _glfwContext;
        Log::shutdown();
    }

    void Framework::initInstance() {
        _instance.reset(new Framework());
    }

    Framework& Framework::getInstance() {
        std::call_once(_initFlag, initInstance);
        return *_instance;
    }

    GLFWContext* Framework::getGlfwContext() const {
        return _glfwContext;
    }

    bool Framework::hasGlfwContext() const {
        return getGlfwContext();
    }

    WindowManager& Framework::getWindowManager() const {
        return *_windowManager;
    }

    EventSystem& Framework::getEventSystem() const {
        return *_eventSystem;
    }

    ResourceManager& Framework::getResourceManager() const {
        if (!_resourceManager) {
            GLFWWindowProperties dummyWindowProps;
            dummyWindowProps.title = "ResourceWindow";
            dummyWindowProps.width = 1;
            dummyWindowProps.height = 1;
            dummyWindowProps.visible = false;
            dummyWindowProps.shouldVSync = true;
            auto& resourceDummyWindow = _instance->_windowManager->createWindow(dummyWindowProps);
            _instance->_resourceManager = new ResourceManager(std::unique_ptr<AbstractResourceFactory>(new OpenGLResourceFactory(resourceDummyWindow.getContext())));
        }
        // ReSharper disable once CppDFANullDereference
        return *_resourceManager;
    }

    void Framework::processEvents() const {
        _eventSystem->dispatchEvents();
    }
}
