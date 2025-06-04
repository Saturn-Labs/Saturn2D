#include "MyApplication.hpp"

#include "Core/Diagnostics/Log.hpp"

MyApplication::MyApplication() :
    Application("MyApplication", "ryd3v") {
    Saturn::Log::trace("Hello, World!");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwCreateWindow(640, 480, "Test", nullptr, nullptr);
    std::cin.get();
}
