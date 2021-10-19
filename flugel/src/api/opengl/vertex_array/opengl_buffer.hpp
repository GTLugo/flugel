#pragma once

#include "core/renderer/vertex_array/buffer.hpp"

namespace fge {
  class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(float* verts, uint32_t bitSize);
    virtual ~OpenGLVertexBuffer() override;

    // set vertex data?

    // virtual uint32_t id() const override { return bufferId_; }
    virtual const BufferLayout& layout() const override { return layout_; }
    virtual void setLayout(const BufferLayout& layout) override { layout_ = layout; }

    virtual void bind() const override;
    virtual void unbind() const override;
  private:
    uint32_t bufferId_;
    BufferLayout layout_;
  };

  class OpenGLIndexBuffer : public IndexBuffer {
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer() override;

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual uint32_t count() const { return count_; }
  private:
    uint32_t bufferId_;
    uint32_t count_;
  };
}