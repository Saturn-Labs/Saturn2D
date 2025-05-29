#pragma once
#include "Core/Graphics/Resource/VertexBuffer.hpp"

namespace Saturn {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        explicit OpenGLVertexBuffer()
            : VertexBuffer(id) {
        }

        OpenGLVertexBuffer(const GraphicsResourceId& id, const void* data, size_t size)
            : VertexBuffer(id, data, size) {
        }

        static
    };
}
