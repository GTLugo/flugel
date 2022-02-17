#pragma once

#include "core/renderer/vertex_array/buffer.hpp"

namespace fge {
  class VertexArray {
  public:
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    [[nodiscard]] virtual u32 indexCount() const = 0;

    virtual void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) = 0;
    virtual void setIndexBuffer(Shared<IndexBuffer> indexBuffer) = 0;

    static Shared<VertexArray> create(Shared<VertexBuffer> vertexBuffer,
                                      Shared<IndexBuffer> indexBuffer);
    static Shared<VertexArray> create(float* vertices, u32 vertBitSize,
                                      const BufferLayout& layout,
                                      u32* indices, u32 count);
    static Shared<VertexArray> create(std::vector<float>& vertices,
                                      const BufferLayout& layout,
                                      std::vector<u32>& indices);
    static Shared<VertexArray> create(const std::initializer_list<float>& vertices,
                                      const BufferLayout& layout,
                                      const std::initializer_list<u32>& indices);
  };
}