//
// Created by galex on 2/20/2022.
//

#include "vulkan_texture_buffer.hpp"

#include "core/app.hpp"

namespace ff {
  VulkanTextureBuffer::VulkanTextureBuffer(TextureBuffer::Format format, i32 width, i32 height, void* data) {
    bind();

    unbind();
  }

  VulkanTextureBuffer::~VulkanTextureBuffer() {

  }

  void VulkanTextureBuffer::bind() const {

  }

  void VulkanTextureBuffer::unbind() const {

  }

  u32 VulkanTextureBuffer::handle() const {
    return textureId_;
  }
}