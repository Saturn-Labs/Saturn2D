#pragma once
#include <memory>

#include "AbstractResourceFactory.hpp"
#include "Core/Window/IWindow.hpp"

namespace Saturn {
    class ResourceManager {
        friend class Framework;
        std::unique_ptr<AbstractResourceFactory> _resourceFactory;

        explicit ResourceManager(std::unique_ptr<AbstractResourceFactory>&& resourceFactory);
        ~ResourceManager() = default;
    public:

        const GraphicsContext& getResourceContext() const;
        AbstractResourceFactory& getResourceFactory() const;
    };
}
