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

    static VertexArray* create(Shared<VertexBuffer> vertexBuffer,
                               Shared<IndexBuffer> indexBuffer);
    static VertexArray* create(float* verts, uint32_t vertBitSize,
                               const BufferLayout& layout,
                               uint32_t* indices, uint32_t count);
    static VertexArray* create(const std::initializer_list<Vertex>& verts,
                               const BufferLayout& layout,
                               const std::initializer_list<uint32_t>& indices);
    static VertexArray* create(std::vector<Vertex>& verts,
                               const BufferLayout& layout,
                               std::vector<uint32_t>& indices);
  };
}