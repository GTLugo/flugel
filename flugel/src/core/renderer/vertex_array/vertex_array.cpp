#include "vertex_array.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/vertex_array/opengl_vertex_array.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace fge {
  Shared<VertexArray> VertexArray::create(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer) {
    
    switch (Renderer::api()) {
      case Renderer::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
          return makeShared<OpenGLVertexArray>(vertexBuffer, indexBuffer);
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

  Shared<VertexArray> VertexArray::create(float* vertices, u32 vertBitSize,
                                          const BufferLayout& layout,
                                          u32* indices, u32 count) {
    FGE_ASSERT_ENG(vertices, "No vertices found for vertex array!");
    auto vbo = VertexBuffer::create(vertices, vertBitSize);
    vbo->bind();
    vbo->setLayout(layout);
    vbo->unbind();
    return create(
      vbo,
      IndexBuffer::create(indices, count)
    );
  }

  Shared<VertexArray> VertexArray::create(std::vector<float>& vertices,
                                          const BufferLayout& layout,
                                          std::vector<u32>& indices) {
    FGE_ASSERT_ENG(vertices.size(), "No vertices found for vertex array!");
    auto vbo = VertexBuffer::create(vertices);
    vbo->bind();
    vbo->setLayout(layout);
    vbo->unbind();
    return create(
      vbo,
      IndexBuffer::create(indices)
    );
  }

  Shared<VertexArray> VertexArray::create(const std::initializer_list<float>& vertices,
                                          const BufferLayout& layout,
                                          const std::initializer_list<u32>& indices) {
    FGE_ASSERT_ENG(vertices.size(), "No vertices found for vertex array!");
    auto vbo = VertexBuffer::create(vertices);
    vbo->bind();
    vbo->setLayout(layout);
    vbo->unbind();
    return create(
      vbo,
      IndexBuffer::create(indices)
    );
  }
}