#pragma once

#include "core/renderer/buffer/buffer.hpp"

namespace ff {
  struct VertexBase {
    VertexBase() = default;
    virtual ~VertexBase() = default;
    virtual std::vector<float> unwind() = 0;
  };

  class VertexArray {
  public:
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    [[nodiscard]] virtual u32 indexCount() const = 0;

    virtual void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) = 0;
    virtual void setIndexBuffer(Shared<IndexBuffer> indexBuffer) = 0;

    static Shared<VertexArray> create(const std::vector<Shared<VertexBuffer>>& vertexBuffers, Shared<IndexBuffer> indexBuffer);

    template<class T>
    static Shared<VertexArray> create(const std::vector<T>& vertices,
                                      const VertexBufferLayout& layout,
                                      const std::vector<u32>& indices) {
      FF_ASSERT_E(vertices.size(), "No vertices found for vertex array!");
      auto vbo = VertexBuffer::create(vertices);
      vbo->setLayout(layout);
      return create(vbo, IndexBuffer::create(indices));
    }
  };
}