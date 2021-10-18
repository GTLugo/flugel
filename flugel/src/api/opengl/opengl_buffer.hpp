#pragma once

#include "core/renderer/buffer.hpp"

namespace fge {
  class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(double* verts, uint32_t bitSize);
    virtual ~OpenGLVertexBuffer();

    // set vertex data?

    virtual void bind() const;
    virtual void unbind() const;
  private:
    uint32_t bufferId_;
  };

  class OpenGLIndexBuffer : public IndexBuffer {
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void bind() const;
    virtual void unbind() const;

    virtual uint32_t count() const { return count_; }
  private:
    uint32_t bufferId_;
    uint32_t count_;
  };
}