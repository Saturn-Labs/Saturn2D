#pragma once
#include <optional>
#include <variant>

#include "Core/Graphics/GraphicsAPI.hpp"
#include "Core/Types/Object.hpp"
#include "glad/gl.h"

namespace Saturn {
    class GraphicsResourceId final : public Object {
        using OpenGLResourceId = GLuint;
        GraphicsAPI _api = GraphicsAPI::Unknown;
        std::variant<std::monostate, OpenGLResourceId> _id = std::monostate{};
    public:
        GraphicsResourceId() = default;
        explicit GraphicsResourceId(OpenGLResourceId id);
        GraphicsResourceId(const GraphicsResourceId& other);
        GraphicsResourceId& operator=(const GraphicsResourceId& other);
        GraphicsResourceId(GraphicsResourceId&& other) noexcept;
        GraphicsResourceId& operator=(GraphicsResourceId&& other) noexcept;

        bool isAPI(const GraphicsAPI& api) const;
        bool isOpenGLResource() const;
        bool isValid() const;

        operator bool() const;
        bool operator==(const GraphicsResourceId& other) const;
        bool operator!=(const GraphicsResourceId& other) const;

        GraphicsAPI getAPI() const;
        OpenGLResourceId getOpenGLResourceId() const;
        std::optional<OpenGLResourceId> tryGetOpenGLResourceId() const;

        static constexpr OpenGLResourceId InvalidOpenGLResourceId = 0;
        static GraphicsResourceId Invalid() {
            return GraphicsResourceId{};
        }

        [[nodiscard]] std::string toString() const override;
    };
}
