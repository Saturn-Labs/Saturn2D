#pragma once
#include <future>

#include "Core/Graphics/Resource/AbstractResourceFactory.hpp"

namespace Saturn {
    class OpenGLResourceFactory final : public AbstractResourceFactory {
        friend class Framework;
        explicit OpenGLResourceFactory(const GraphicsContext& ctx) :
            AbstractResourceFactory(ctx) {
        }
        ~OpenGLResourceFactory() override = default;
    public:
        std::future<GraphicsResourceId> createBuffer() override;
    };
}