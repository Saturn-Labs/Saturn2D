#include "Core/Graphics/Resource/OpenGL/OpenGLResourceFactory.hpp"

#include <future>

namespace Saturn {
    std::future<GraphicsResourceId> OpenGLResourceFactory::createBuffer() {
        auto future = std::async(std::launch::async, [this] {
            _creationContext.makeCurrent();
            GLuint buffer = 0;
            glGenBuffers(1, &buffer);
            return GraphicsResourceId(buffer);
        });
        return future;
    }
}
