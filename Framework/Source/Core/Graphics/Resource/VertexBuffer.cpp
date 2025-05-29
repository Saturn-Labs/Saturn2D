#include "Core/Graphics/Resource/VertexBuffer.hpp"

namespace Saturn {
    VertexBuffer::VertexBuffer(const GraphicsResourceId& id) :
        GraphicsBuffer(nullptr, 0),
        _id(id) {
    }

    VertexBuffer::VertexBuffer(const GraphicsResourceId& id, const void* data, const size_t size) :
        GraphicsBuffer(data, size),
        _id(id) {
    }

    GraphicsResourceId VertexBuffer::getId() const {
        return _id;
    }

    bool VertexBuffer::isValid() const {
        return _id.isValid();
    }
}
