#include <iostream>

#include "Precompiled.hpp"
#include "Core/Framework.hpp"
#include "Core/Logging/Log.hpp"

using namespace Saturn;

int main(const int argc, const char* argv[]) {
    auto& fw = Framework::getInstance();
    auto& windowManager = fw.getWindowManager();

    for (int i = 0; i < 1; i++) {
        WindowProperties props;
        props.title = "Saturn " + std::to_string(i + 1);
        props.width = 640;
        props.height = 480;
        windowManager.createWindow(props).setVSync(false);
    }

    Log::trace("Hello, World!");

    while (windowManager.hasVisibleWindows()) {
        windowManager.updateWindows([](IWindow& window) {
            glClear(GL_COLOR_BUFFER_BIT);
        });
    }
    return 0;
}