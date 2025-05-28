#pragma once
#include <optional>
#include <stdexcept>
#include <variant>
#include <glad/gl.h>

namespace Saturn {
    struct GraphicsResourceHandle {
        using GlHandle = GLuint;
    private:
        std::variant<std::monostate, GlHandle> _handle;

    public:
        GraphicsResourceHandle() = default;
        explicit GraphicsResourceHandle(GlHandle handle) :
            _handle(handle) {
        }

        bool isGlHandle() const {
            return std::holds_alternative<GlHandle>(_handle);
        }

        GlHandle getGlHandle() const {
            if (!isGlHandle())
                throw std::runtime_error("Trying to access GraphicsResourceHandle as GlHandle, but it isn't a GlHandle.");
            return std::get<GlHandle>(_handle);
        }

        std::optional<GlHandle> tryGetGlHandle() const {
            if (!isGlHandle())
                return std::nullopt;
            return std::optional(std::get<GlHandle>(_handle));
        }

        bool isValid() const {
            return !_handle.valueless_by_exception() && _handle.index() != 0;
        }

        bool operator==(const GraphicsResourceHandle& other) const {
            return _handle == other._handle;
        }

        bool operator!=(const GraphicsResourceHandle& other) const {
            return !(*this == other);
        }

        void reset() {
            _handle = std::monostate{};
        }
    };
}