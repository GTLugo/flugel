#include "buffer.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/framebuffer/opengl_buffer.hpp"
#endif
#if defined(FLUGEL_USE_VULKAN)
  #include "api/vulkan/framebuffer/vulkan_buffer.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace ff {
  Shared<VertexBuffer> VertexBuffer::create(const void* vertices, u32 bitSize) {
    FF_ASSERT_E(vertices, "No vertices found for vertex buffer!");
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLVertexBuffer>(vertices, bitSize);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        return makeShared<VulkanVertexBuffer>(vertices, bitSize);
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
          return nullptr;
        #endif
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        return nullptr;
      }
    }
  }

  Shared<IndexBuffer> IndexBuffer::create(const u32* indices, u32 count) {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
          return makeShared<OpenGLIndexBuffer>(indices, count);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        return makeShared<VulkanIndexBuffer>(indices, count);
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
          return nullptr;
        #endif
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        return nullptr;
      }
    }
  }
  
  Shared<IndexBuffer> IndexBuffer::create(const std::vector<u32>& indices) {
    return create(indices.data(), static_cast<u32>(indices.size()));
  }
}