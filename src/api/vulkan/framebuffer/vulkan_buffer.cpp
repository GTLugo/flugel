#include "vulkan_buffer.hpp"

#include "core/app.hpp"

namespace ff {

  // VERTEX BUFFER --------------------------- //

  VulkanVertexBuffer::VulkanVertexBuffer(const void* verts, u32 bitSize) {

  }

  VulkanVertexBuffer::~VulkanVertexBuffer() {

  }

  void VulkanVertexBuffer::bind() const {

  }

  void VulkanVertexBuffer::unbind() const {

  }

  void VulkanVertexBuffer::setLayout(const VertexBufferLayout& layout) {

  }

  // INDEX BUFFER --------------------------- //

  VulkanIndexBuffer::VulkanIndexBuffer(const u32* indices, u32 count)
    : count_{count} {

  }

  VulkanIndexBuffer::~VulkanIndexBuffer() {

  }

  void VulkanIndexBuffer::bind() const {

  }

  void VulkanIndexBuffer::unbind() const {

  }
}