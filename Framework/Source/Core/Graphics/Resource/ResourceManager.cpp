#include "Core/Graphics/Resource/ResourceManager.hpp"

namespace Saturn {
    ResourceManager::ResourceManager(std::unique_ptr<AbstractResourceFactory>&& resourceFactory) :
        _resourceFactory(std::move(resourceFactory)) {
    }

    const GraphicsContext& ResourceManager::getResourceContext() const {
        return _resourceFactory->getCreationContext();
    }

    AbstractResourceFactory& ResourceManager::getResourceFactory() const {
        return *_resourceFactory;
    }
}
