//
// Created by galex on 2/20/2022.
//

#include "vulkan_frame_buffer.hpp"

#include "core/app.hpp"

namespace ff {
  VulkanFrameBuffer::VulkanFrameBuffer(TextureBuffer::Format format, i32 width, i32 height, void* data) {
    bind();

    unbind();
  }

  VulkanFrameBuffer::VulkanFrameBuffer(const Shared<TextureBuffer>& textureBuffer) {
    bind();

    unbind();
  }

  VulkanFrameBuffer::~VulkanFrameBuffer() {

  }

  void VulkanFrameBuffer::bind() const {

  }

  void VulkanFrameBuffer::unbind() const {

  }
}