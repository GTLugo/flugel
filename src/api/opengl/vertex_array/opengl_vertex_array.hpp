#pragma once

#include "core/renderer/vertex_array/vertex_array.hpp"

namespace ff {
  class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer);
    ~OpenGLVertexArray() override;

    void bind() const override;
    void unbind() const override;

    [[nodiscard]] u32 indexCount() const override { return indexBuffer_->count(); };

    void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) final;
    void setIndexBuffer(Shared<IndexBuffer> indexBuffer) final;
  private:
    u32 vertexArrayId_{};
    std::vector<Shared<VertexBuffer>> vertexBuffers_;
    Shared<IndexBuffer> indexBuffer_;
  };
}