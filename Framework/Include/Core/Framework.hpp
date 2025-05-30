#pragma once
#include <memory>
#include <mutex>

#include "Event/EventSystem.hpp"
#include "Graphics/Resource/ResourceManager.hpp"
#include "Platform/GLFW/GLFWContext.hpp"
#include "Window/IWindowFactory.hpp"
#include "Window/Management/WindowManager.hpp"

namespace Saturn {
    class Framework {
    private:
        static std::unique_ptr<Framework> _instance;
        static std::once_flag _initFlag;

        GLFWContext* _glfwContext = nullptr;
        WindowManager* _windowManager = nullptr;
        EventSystem* _eventSystem = nullptr;
        ResourceManager* _resourceManager = nullptr;

        Framework();
        static void initInstance();

    public:
        ~Framework();
        Framework(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework& operator=(Framework&&) = delete;
        static Framework& getInstance();
        GLFWContext* getGlfwContext() const;
        bool hasGlfwContext() const;
        WindowManager& getWindowManager() const;
        EventSystem& getEventSystem() const;
        ResourceManager& getResourceManager() const;
        void processEvents() const;
    };
}
