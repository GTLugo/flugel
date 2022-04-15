//
// Created by galex on 2/20/2022.
//

#pragma once

#include "core/renderer/buffer/texture_buffer.hpp"

namespace ff {
  class VulkanTextureBuffer final : public TextureBuffer {
  public:
    VulkanTextureBuffer(Format format, i32 width, i32 height, void* data);
    ~VulkanTextureBuffer() final;

    void bind() const final;
    void unbind() const final;

    u32 handle() const final;
  private:
    u32 textureId_{};
  };
}

