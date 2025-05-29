#pragma once
#include "GraphicsResourceId.hpp"

namespace Saturn {
    class GraphicsBuffer {
        void* _data = nullptr;
        size_t _size = 0;
    protected:
        GraphicsBuffer();
        GraphicsBuffer(const void* data, size_t size);
        GraphicsBuffer(const GraphicsBuffer& other);
        GraphicsBuffer& operator=(const GraphicsBuffer& other);
        GraphicsBuffer(GraphicsBuffer&& other) noexcept;
        GraphicsBuffer& operator=(GraphicsBuffer&& other) noexcept;
        virtual ~GraphicsBuffer();
    public:
        virtual void setData(const void* data, size_t size);

        virtual GraphicsResourceId getId() const = 0;
        virtual void uploadData() = 0;
        virtual bool isValid() const = 0;

        bool hasData() const;
    };
}
