#include "Precompiled.hpp"
#include "Core/Application/Application.hpp"
#include "Core/Diagnostics/Log.hpp"

#if defined(SATURN_FX_MAIN)
int main(const Saturn::i32 argc, Saturn::CString argv[]) {
    using namespace Saturn;
    auto application = CreateApplication(argc, argv);
    return 0;
}
#endif