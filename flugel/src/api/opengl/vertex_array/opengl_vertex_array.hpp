#pragma once

#include "core/renderer/vertex_array/vertex_array.hpp"

namespace fge {
  class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer);
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

<<<<<<< Updated upstream
    virtual uint32_t indexCount() const override { return indexBuffer_->count(); };
=======
    virtual u32 indexCount() const override { return indexBuffer_->count(); };
>>>>>>> Stashed changes

    virtual void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) override;
    virtual void setIndexBuffer(Shared<IndexBuffer> indexBuffer) override;
  private:
<<<<<<< Updated upstream
    uint32_t vertexArrayId_;
=======
    u32 vertexArrayId_;
>>>>>>> Stashed changes
    std::vector<Shared<VertexBuffer>> vertexBuffers_;
    Shared<IndexBuffer> indexBuffer_;
  };
}