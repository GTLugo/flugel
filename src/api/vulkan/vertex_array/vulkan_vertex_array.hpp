#pragma once

#include "core/renderer/vertex_array/vertex_array.hpp"

namespace ff {
  class VulkanVertexArray : public VertexArray {
  public:
    VulkanVertexArray(const std::vector<Shared<VertexBuffer>>& vertexBuffers, Shared<IndexBuffer> indexBuffer);
    ~VulkanVertexArray() override;

    void bind() const override;
    void unbind() const override;

    [[nodiscard]] u32 indexCount() const override { return indexBuffer_->count(); };

    void addVertexBuffer(Shared<VertexBuffer> vertexBuffer) final;
    void setIndexBuffer(Shared<IndexBuffer> indexBuffer) final;
  private:
    u32 vertexArrayId_{};
    std::vector<Shared<VertexBuffer>> vertexBuffers_;
    Shared<IndexBuffer> indexBuffer_;
    u32 location_{0};
  };
}