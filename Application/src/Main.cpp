#include "MyApplication.hpp"
#include "Precompiled.hpp"
#include "Core/Application/Application.hpp"

namespace Saturn {
    Unique<Application> CreateApplication(i32 argc, CString argv[]) {
        return createUnique<MyApplication>();
    }
}