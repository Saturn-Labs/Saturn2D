#include "MyApplication.hpp"

#include "Core/Diagnostics/Log.hpp"

MyApplication::MyApplication() :
    Application("MyApplication", "ryd3v") {
    Saturn::Log::trace("Hello, World!");
    std::cin.get();
}
