#pragma once

#include "core/renderer/buffer/buffer.hpp"

namespace ff {
  struct Vertex {
    vec3 pos{0.f, 0.f, 0.f};
    vec4 color{1.f, 0.f, 1.f, 1.f};
    vec2 uv{0.f, 0.f};


//    Vertex(vec3 pos_)
//        : position{pos_}, color{std::nullopt}, uv{std::nullopt} {}
//    Vertex(vec3 pos_, vec4 color_, vec2 uv_)
//        : position{pos_}, color{color_}, uv{uv_} {}
  };

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
                                      const VertexBufferLayout& layout,
                                      u32* indices, u32 count);
    static Shared<VertexArray> create(std::vector<float>& vertices,
                                      const VertexBufferLayout& layout,
                                      std::vector<u32>& indices);
    static Shared<VertexArray> create(const std::initializer_list<float>& vertices,
                                      const VertexBufferLayout& layout,
                                      const std::initializer_list<u32>& indices);
  };
}