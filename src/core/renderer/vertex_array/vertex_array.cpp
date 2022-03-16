#include "vertex_array.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/vertex_array/opengl_vertex_array.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace ff {
  Shared<VertexArray> VertexArray::create(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer) {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
          return makeShared<OpenGLVertexArray>(vertexBuffer, indexBuffer);
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

  Shared<VertexArray> VertexArray::create(float* vertices, u32 vertBitSize,
                                          const VertexBufferLayout& layout,
                                          u32* indices, u32 count) {
    FF_ASSERT_E(vertices, "No vertices found for vertex array!");
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
                                          const VertexBufferLayout& layout,
                                          std::vector<u32>& indices) {
    FF_ASSERT_E(vertices.size(), "No vertices found for vertex array!");
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
                                          const VertexBufferLayout& layout,
                                          const std::initializer_list<u32>& indices) {
    FF_ASSERT_E(vertices.size(), "No vertices found for vertex array!");
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