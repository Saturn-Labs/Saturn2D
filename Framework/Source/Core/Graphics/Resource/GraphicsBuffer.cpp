#pragma once
#include "Core/Graphics/Resource/GraphicsBuffer.hpp"
#include <stdlib.h>
#include <string.h>
#include <utility>

namespace Saturn {
    GraphicsBuffer::GraphicsBuffer() = default;
    GraphicsBuffer::GraphicsBuffer(const void* data, const size_t size) {
        GraphicsBuffer::setData(data, size);
    }

    GraphicsBuffer::GraphicsBuffer(const GraphicsBuffer& other) {
        GraphicsBuffer::setData(other._data, other._size);
    }

    GraphicsBuffer& GraphicsBuffer::operator=(const GraphicsBuffer& other) {
        if (this != &other) {
            GraphicsBuffer::setData(other._data, other._size);
        }
        return *this;
    }

    GraphicsBuffer::GraphicsBuffer(GraphicsBuffer&& other) noexcept :
        _data(std::exchange(other._data, nullptr)),
        _size(std::exchange(other._size, 0)) {
    }

    GraphicsBuffer& GraphicsBuffer::operator=(GraphicsBuffer&& other) noexcept {
        if (this != &other) {
            _data = std::exchange(other._data, nullptr);
            _size = std::exchange(other._size, 0);
        }
        return *this;
    }

    GraphicsBuffer::~GraphicsBuffer() {
        free(_data);
        _data = nullptr;
        _size = 0;
    }

    void GraphicsBuffer::setData(const void* data, const size_t size) {
        if (!data || size == 0)
            return;
        free(_data);
        _data = nullptr;
        _data = malloc(size);
        memcpy(_data, data, size);
        _size = size;
    }

    bool GraphicsBuffer::hasData() const {
        return _data && _size != 0;
    }
}
