#pragma once
#include "GraphicsBuffer.hpp"
#include "IBindableResource.hpp"

namespace Saturn {
    class VertexBuffer : public GraphicsBuffer, public IBindableResource<bool(), void()> {
        GraphicsResourceId _id;
    protected:
        explicit VertexBuffer(const GraphicsResourceId& id);
        VertexBuffer(const GraphicsResourceId& id, const void* data, size_t size);
    public:
        GraphicsResourceId getId() const override;
        bool isValid() const override;
    };
}
