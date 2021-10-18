#include "buffer.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/opengl_buffer.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace fge {
  VertexBuffer* VertexBuffer::create(float* verts, uint32_t bitSize) {
    switch (Renderer::api()) {
      case Renderer::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
          return new OpenGLVertexBuffer{verts, bitSize};
        #else
          FGE_ASSERT_ENG(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
          FGE_ASSERT_ENG(false, "Vulkan not implemented!");
          return nullptr;
        #else
          FGE_ASSERT_ENG(false, "Vulkan not supported!");
          return nullptr;
        #endif
      }
      case Renderer::D3D11: {
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

  VertexBuffer* VertexBuffer::create(std::vector<Vertex>& verts) {
    std::vector<float> v;
    for (auto& vert : verts) {
      v.push_back(vert.position.x);
      v.push_back(vert.position.y);
      v.push_back(vert.position.z);
      v.push_back(vert.color.r);
      v.push_back(vert.color.g);
      v.push_back(vert.color.b);
      v.push_back(vert.color.a);
    }
    return create(v.data(), v.size() * sizeof(v[0]));
  }

  IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count) {
    switch (Renderer::api()) {
      case Renderer::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
          return new OpenGLIndexBuffer{indices, count};
        #else
          FGE_ASSERT_ENG(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
          FGE_ASSERT_ENG(false, "Vulkan not implemented!");
          return nullptr;
        #else
          FGE_ASSERT_ENG(false, "Vulkan not supported!");
          return nullptr;
        #endif
      }
      case Renderer::D3D11: {
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
  
  IndexBuffer* IndexBuffer::create(std::vector<uint32_t>& indices) {
    return create(indices.data(), indices.size());
  }
}