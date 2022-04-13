//
// Created by galex on 2/20/2022.
//

#include "texture_buffer.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/framebuffer/opengl_texture_buffer.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace ff {
  Shared<TextureBuffer> TextureBuffer::create(Format format, i32 width, i32 height, void* data) {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLTextureBuffer>(format, width, height, data);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FGE_ASSERT_ENG(false, "D3D11 not implemented!");
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
}