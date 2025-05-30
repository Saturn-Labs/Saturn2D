#pragma once
#include "GraphicsResourceId.hpp"
#include "Core/Window/IWindow.hpp"
#include <future>

namespace Saturn {
    class AbstractResourceFactory {
    protected:
        const GraphicsContext& _creationContext;

        explicit AbstractResourceFactory(const GraphicsContext& ctx) :
            _creationContext(ctx) {
        }
    public:
        virtual ~AbstractResourceFactory() = default;
        virtual std::future<GraphicsResourceId> createBuffer() = 0;
        const GraphicsContext& getCreationContext() const { return _creationContext; }
    };
}
