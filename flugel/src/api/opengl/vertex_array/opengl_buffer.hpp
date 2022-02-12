#pragma once

#include "core/renderer/vertex_array/buffer.hpp"

namespace fge {
  class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(float* verts, u32 bitSize);
    virtual ~OpenGLVertexBuffer() override;

    // set vertex data?

    // virtual u32 id() const override { return bufferId_; }
    virtual const BufferLayout& layout() const override { return layout_; }
    virtual void setLayout(const BufferLayout& layout) override { layout_ = layout; }

    virtual void bind() const override;
    virtual void unbind() const override;
  private:
    u32 bufferId_;
    BufferLayout layout_;
  };

  class OpenGLIndexBuffer : public IndexBuffer {
  public:
    OpenGLIndexBuffer(u32* indices, u32 count);
    virtual ~OpenGLIndexBuffer() override;

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual u32 count() const { return count_; }
  private:
    u32 bufferId_;
    u32 count_;
  };
}