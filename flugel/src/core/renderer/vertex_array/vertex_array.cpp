#include "vertex_array.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/vertex_array/opengl_vertex_array.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace fge {
  VertexArray* VertexArray::create(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer) {
    switch (Renderer::api()) {
      case Renderer::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
          return new OpenGLVertexArray{vertexBuffer, indexBuffer};
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

  VertexArray* VertexArray::create(float* verts, uint32_t vertBitSize,
                                   const BufferLayout& layout,
                                   uint32_t* indices, uint32_t count) {
    auto vbo = Shared<VertexBuffer>(VertexBuffer::create(verts, vertBitSize));
    vbo->setLayout(layout);
    return create(
      vbo,
      Shared<IndexBuffer>(IndexBuffer::create(indices, count))
    );
  }

  VertexArray* VertexArray::create(const std::initializer_list<Vertex>& verts,
                                   const BufferLayout& layout,
                                   const std::initializer_list<uint32_t>& indices) {
    auto vbo = Shared<VertexBuffer>(VertexBuffer::create(verts));
    vbo->setLayout(layout);
    return create(
      vbo,
      Shared<IndexBuffer>(IndexBuffer::create(indices))
    );
  }

  VertexArray* VertexArray::create(std::vector<Vertex>& verts,
                                   const BufferLayout& layout,
                                   std::vector<uint32_t>& indices) {
    auto vbo = Shared<VertexBuffer>(VertexBuffer::create(verts));
    vbo->setLayout(layout);
    return create(
      vbo,
      Shared<IndexBuffer>(IndexBuffer::create(indices))
    );
  }
}