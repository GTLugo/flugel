//
// Created by galex on 2/20/2022.
//

#pragma once

#include "core/renderer/buffer/frame_buffer.hpp"

namespace ff {
  class VulkanFrameBuffer : public FrameBuffer {
  public:
    VulkanFrameBuffer(TextureBuffer::Format format, i32 width, i32 height, void* data);
    explicit VulkanFrameBuffer(const Shared<TextureBuffer>& textureBuffer);
    ~VulkanFrameBuffer() override;

    void bind() const final;
    void unbind() const final;
  private:
    u32 frameBufferId_{};
  };
}

