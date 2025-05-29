#include "Precompiled.hpp"
#include "Core/Framework.hpp"
#include "Core/Event/Window/FramebufferResizeEvent.hpp"
#include "Core/Event/Window/WindowCloseEvent.hpp"
#include "Core/Event/Window/WindowResizeEvent.hpp"
#include "Core/Window/GLFW/ScopedOpenGLContext.hpp"
#include "Core/Window/GLFW/WindowProps/GLFWWindowProperties.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

using namespace Saturn;

int main(const int argc, const char* argv[]) {
    auto& fw = Framework::getInstance();
    auto& windowManager = fw.getWindowManager();

    GLFWWindowProperties props;
    props.title = "Saturn 1";
    props.width = 640;
    props.height = 480;
    IWindow& window = windowManager.createWindow(props);
    window.setVSync(false);

    // Cube vertices (X, Y, Z)
    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f, // 0: Left  Bottom Back
         0.5f, -0.5f, -0.5f, // 1: Right Bottom Back
         0.5f,  0.5f, -0.5f, // 2: Right Top    Back
        -0.5f,  0.5f, -0.5f, // 3: Left  Top    Back
        -0.5f, -0.5f,  0.5f, // 4: Left  Bottom Front
         0.5f, -0.5f,  0.5f, // 5: Right Bottom Front
         0.5f,  0.5f,  0.5f, // 6: Right Top    Front
        -0.5f,  0.5f,  0.5f  // 7: Left  Top    Front
    };

    glm::mat4 model;
    glm::quat rot = glm::quat(glm::vec3(0.785398163, 0.785398163, 0));
    model = glm::toMat4(rot);

    for (int i = 0; i < 24; i += 3) {
        glm::vec3 vertex = glm::vec3(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2]);
        vertex = glm::vec4(vertex, 1.0f) * model;
        cubeVertices[i] = vertex.x;
        cubeVertices[i + 1] = vertex.y;
        cubeVertices[i + 2] = vertex.z;
    }

    unsigned int cubeIndices[] = {
        // Back face
        0, 1, 2,
        2, 3, 0,

        // Front face
        4, 5, 6,
        6, 7, 4,

        // Left face
        0, 4, 7,
        7, 3, 0,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Bottom face
        0, 1, 5,
        5, 4, 0,

        // Top face
        3, 2, 6,
        6, 7, 3
    };

    GLuint vao;
    {
        ScopedOpenGLContext ctx(window.getNativeHandle().getGlfwHandle());
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, cubeVertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, cubeIndices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    fw.getEventSystem().addListener(EventType::FramebufferResize, [](const Event& e) {
        auto& event = dynamic_cast<const FramebufferResizeEvent&>(e);
        ScopedOpenGLContext ctx(event.getWindow().getNativeHandle().getGlfwHandle());
        glViewport(0, 0, event.getWidth(), event.getHeight());
        return false;
    });



    while (windowManager.hasVisibleWindows()) {
        windowManager.updateWindows([&](IWindow& window) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        });
        fw.processEvents();
        windowManager.destroyWindows();
    }
    return 0;
}