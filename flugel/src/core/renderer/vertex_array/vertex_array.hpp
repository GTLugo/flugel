#pragma once

#include "core/renderer/vertex_array/buffer.hpp"

namespace fge {
  class VertexArray {
  public:
    virtual ~VertexArray() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual uint32_t indexCount() const = 0;

    virtual void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) = 0;
    virtual void setIndexBuffer(Shared<IndexBuffer> indexBuffer) = 0;

    static Shared<VertexArray> create(Shared<VertexBuffer> vertexBuffer,
                                      Shared<IndexBuffer> indexBuffer);
    static Shared<VertexArray> create(float* vertices, uint32_t vertBitSize,
                                      const BufferLayout& layout,
                                      uint32_t* indices, uint32_t count);
    static Shared<VertexArray> create(std::vector<float>& vertices,
                                      const BufferLayout& layout,
                                      std::vector<uint32_t>& indices);
    static Shared<VertexArray> create(const std::initializer_list<float>& vertices,
                                      const BufferLayout& layout,
                                      const std::initializer_list<uint32_t>& indices);
  };
}