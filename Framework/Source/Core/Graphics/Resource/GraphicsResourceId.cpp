#include "Core/Graphics/Resource/GraphicsResourceId.hpp"

#include <utility>

namespace Saturn {
    GraphicsResourceId::GraphicsResourceId(OpenGLResourceId id) :
        _id(id),
        _api(GraphicsAPI::OpenGL) {
    }

    GraphicsResourceId::GraphicsResourceId(const GraphicsResourceId& other) :
        _id(other._id),
        _api(other._api) {
    }

    GraphicsResourceId& GraphicsResourceId::operator=(const GraphicsResourceId& other) {
        if (this != &other) {
            _id = other._id;
            _api = other._api;
        }
        return *this;
    }

    GraphicsResourceId::GraphicsResourceId(GraphicsResourceId&& other) noexcept {
        _id = std::exchange(other._id, std::monostate{});
        _api = std::exchange(other._api, GraphicsAPI::Unknown);
    }

    GraphicsResourceId& GraphicsResourceId::operator=(GraphicsResourceId&& other) noexcept {
        if (this != &other) {
            _id = std::exchange(other._id, std::monostate{});
            _api = std::exchange(other._api, GraphicsAPI::Unknown);
        }
        return *this;
    }

    bool GraphicsResourceId::isAPI(const GraphicsAPI& api) const {
        return _api == api;
    }

    GraphicsAPI GraphicsResourceId::getAPI() const {
        return _api;
    }

    bool GraphicsResourceId::isOpenGLResource() const {
        return isValid() && std::holds_alternative<OpenGLResourceId>(_id) && _api == GraphicsAPI::OpenGL;
    }

    bool GraphicsResourceId::isValid() const {
        return !_id.valueless_by_exception() && !std::holds_alternative<std::monostate>(_id) && _api != GraphicsAPI::Unknown;
    }

    GraphicsResourceId::operator bool() const {
        return isValid();
    }

    bool GraphicsResourceId::operator==(const GraphicsResourceId& other) const {
        return _id == other._id;
    }

    bool GraphicsResourceId::operator!=(const GraphicsResourceId& other) const {
        return _id != other._id;
    }

    GraphicsResourceId::OpenGLResourceId GraphicsResourceId::getOpenGLResourceId() const {
        return std::get<OpenGLResourceId>(_id);
    }

    std::optional<GraphicsResourceId::OpenGLResourceId> GraphicsResourceId::tryGetOpenGLResourceId() const {
        if (isOpenGLResource()) {
            return getOpenGLResourceId();
        }
        return std::nullopt;
    }

    std::string GraphicsResourceId::toString() const {
        if (!isValid())
            return "[Invalid Graphics Resource]";

        switch (_api) {
            case GraphicsAPI::OpenGL:
                return "[OpenGL Resource: " + std::to_string(std::get<OpenGLResourceId>(_id)) + "]";
            default:
                return "[UnknownAPI Graphics Resource]";
        }
    }
}
