#pragma once

#include "core/renderer/buffer/buffer.hpp"

namespace ff {
  class VulkanVertexBuffer : public VertexBuffer {
  public:
    VulkanVertexBuffer(const void* verts, u32 bitSize);
    ~VulkanVertexBuffer() override;

    // set vertex data?

    // virtual u32 id() const override { return bufferId_; }
    [[nodiscard]] const VertexBufferLayout& layout() const override { return layout_; }
    void setLayout(const VertexBufferLayout& layout) override;

    void bind() const override;
    void unbind() const override;
  private:
    u32 bufferId_;
    VertexBufferLayout layout_;
  };

  class VulkanIndexBuffer : public IndexBuffer {
  public:
    VulkanIndexBuffer(const u32* indices, u32 count);
    ~VulkanIndexBuffer() override;

    void bind() const override;
    void unbind() const override;

    [[nodiscard]] u32 count() const override { return count_; }
  private:
    u32 bufferId_;
    u32 count_;
  };
}