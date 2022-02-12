#pragma once

#include "core/renderer/vertex_array/vertex_array.hpp"

namespace fge {
  class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer);
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual u32 indexCount() const override { return indexBuffer_->count(); };

    virtual void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) override;
    virtual void setIndexBuffer(Shared<IndexBuffer> indexBuffer) override;
  private:
    u32 vertexArrayId_;
    std::vector<Shared<VertexBuffer>> vertexBuffers_;
    Shared<IndexBuffer> indexBuffer_;
  };
}