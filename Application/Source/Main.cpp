#include <GL/gl.h>
#include "Precompiled.hpp"
#include "Core/Framework.hpp"
#include "Core/Event/Window/FramebufferResizeEvent.hpp"
#include "Core/Event/Window/WindowCloseEvent.hpp"
#include "Core/Event/Window/WindowResizeEvent.hpp"
#include "Core/Window/GLFW/ScopedContext.hpp"
#include "Core/Window/GLFW/WindowProps/GLFWWindowProperties.hpp"

using namespace Saturn;

int main(const int argc, const char* argv[]) {
    auto& fw = Framework::getInstance();
    auto& windowManager = fw.getWindowManager();

    for (int i = 0; i < 1; i++) {
        GLFWWindowProperties props;
        props.title = "Saturn " + std::to_string(i + 1);
        props.width = 640;
        props.height = 480;
        windowManager.createWindow(props).setVSync(false);
    }

    fw.getEventSystem().addListener(EventType::FramebufferResize, [](const Event& e) {
        auto& event = dynamic_cast<const FramebufferResizeEvent&>(e);
        ScopedContext ctx(event.getWindow().getNativeHandle().getGlfwHandle());
        glViewport(0, 0, event.getWidth(), event.getHeight());
        return false;
    });

    while (windowManager.hasVisibleWindows()) {
        windowManager.updateWindows([](IWindow& window) {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, -0.5f, 0.0f);
            glEnd();
        });
        fw.processEvents();
        windowManager.destroyWindows();
    }
    return 0;
}