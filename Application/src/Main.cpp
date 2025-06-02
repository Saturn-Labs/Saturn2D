#include "Precompiled.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Core/Diagnostics/Log.hpp"

int main(const int argc, const char* argv[]) {
    Saturn::Log::init("Saturn2D");
    Saturn::Log::warn("Hello World!");
    std::cin.get();
    return 0;
}
