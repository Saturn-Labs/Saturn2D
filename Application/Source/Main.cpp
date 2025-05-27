#include <iostream>

#include "Precompiled.hpp"
#include "Core/Framework.hpp"

using namespace Saturn;

int main(const int argc, const char* argv[]) {
    auto& fw = Framework::getInstance();
    auto& windowManager = fw.getWindowManager();

    for (int i = 0; i < 4; i++) {
        WindowProperties props;
        props.title = "Saturn " + std::to_string(i);
        props.width = 800;
        props.height = 600;
        windowManager.createWindow(props);
    }


    while (windowManager.hasVisibleWindows()) {
        windowManager.renderWindows([](IWindow& window) {
            glClear(GL_COLOR_BUFFER_BIT);
        });
    }
    return 0;
}