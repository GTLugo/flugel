//
// Created by galex on 2/20/2022.
//
#include "frame_buffer.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/framebuffer/opengl_frame_buffer.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace fge {
  Shared<FrameBuffer> FrameBuffer::create(TextureBuffer::Format format, i32 width, i32 height, void* data) {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLFrameBuffer>(format, width, height, data);
        #else
        FGE_ASSERT_ENG(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FGE_ASSERT_ENG(false, "Vulkan not implemented!");
          return nullptr;
        #else
        FGE_ASSERT_ENG(false, "Vulkan not supported!");
        return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FGE_ASSERT_ENG(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FGE_ASSERT_ENG(false, "D3D11 not supported!");
        return nullptr;
        #endif
      }
      default: {
        FGE_ASSERT_ENG(false, "Unknown render api!");
        return nullptr;
      }
    }
  }

  Shared<FrameBuffer> FrameBuffer::create(const Shared<TextureBuffer>& textureBuffer) {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLFrameBuffer>(textureBuffer);
        #else
        FGE_ASSERT_ENG(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FGE_ASSERT_ENG(false, "Vulkan not implemented!");
          return nullptr;
        #else
        FGE_ASSERT_ENG(false, "Vulkan not supported!");
        return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FGE_ASSERT_ENG(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FGE_ASSERT_ENG(false, "D3D11 not supported!");
        return nullptr;
        #endif
      }
      default: {
        FGE_ASSERT_ENG(false, "Unknown render api!");
        return nullptr;
      }
    }
  }
}