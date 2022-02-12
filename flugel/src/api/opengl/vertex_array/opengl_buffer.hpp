#pragma once

#include "core/renderer/vertex_array/buffer.hpp"

namespace fge {
  class OpenGLVertexBuffer : public VertexBuffer {
  public:
<<<<<<< Updated upstream
    OpenGLVertexBuffer(float* verts, uint32_t bitSize);
=======
    OpenGLVertexBuffer(float* verts, u32 bitSize);
>>>>>>> Stashed changes
    virtual ~OpenGLVertexBuffer() override;

    // set vertex data?

<<<<<<< Updated upstream
    // virtual uint32_t id() const override { return bufferId_; }
=======
    // virtual u32 id() const override { return bufferId_; }
>>>>>>> Stashed changes
    virtual const BufferLayout& layout() const override { return layout_; }
    virtual void setLayout(const BufferLayout& layout) override { layout_ = layout; }

    virtual void bind() const override;
    virtual void unbind() const override;
  private:
<<<<<<< Updated upstream
    uint32_t bufferId_;
=======
    u32 bufferId_;
>>>>>>> Stashed changes
    BufferLayout layout_;
  };

  class OpenGLIndexBuffer : public IndexBuffer {
  public:
<<<<<<< Updated upstream
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
=======
    OpenGLIndexBuffer(u32* indices, u32 count);
>>>>>>> Stashed changes
    virtual ~OpenGLIndexBuffer() override;

    virtual void bind() const override;
    virtual void unbind() const override;

<<<<<<< Updated upstream
    virtual uint32_t count() const { return count_; }
  private:
    uint32_t bufferId_;
    uint32_t count_;
=======
    virtual u32 count() const { return count_; }
  private:
    u32 bufferId_;
    u32 count_;
>>>>>>> Stashed changes
  };
}