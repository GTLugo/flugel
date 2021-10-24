#include "opengl_vertex_array.hpp"

#include <glad/gl.h>

namespace fge {
  static GLenum shaderDataToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
      case ShaderDataType::Bool:   { return GL_BOOL; }
      case ShaderDataType::Int:    { return GL_INT; }
      case ShaderDataType::Int2:   { return GL_INT; }
      case ShaderDataType::Int3:   { return GL_INT; }
      case ShaderDataType::Int4:   { return GL_INT; }
      case ShaderDataType::Float:  { return GL_FLOAT; }
      case ShaderDataType::Float2: { return GL_FLOAT; }
      case ShaderDataType::Float3: { return GL_FLOAT; }
      case ShaderDataType::Float4: { return GL_FLOAT; }
      case ShaderDataType::Mat3:   { return GL_FLOAT; }
      case ShaderDataType::Mat4:   { return GL_FLOAT; }
      default:                     { return 0; }
    }
  }

  OpenGLVertexArray::~OpenGLVertexArray() {
    //auto gl{gladGetGLContext()};
    
    glDeleteVertexArrays(1, &vertexArrayId_);
  }

  OpenGLVertexArray::OpenGLVertexArray(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer) {
    //auto gl{gladGetGLContext()};

    glCreateVertexArrays(1, &vertexArrayId_);
    addVertexBuffer(vertexBuffer);
    setIndexBuffer(indexBuffer);
  }

  void OpenGLVertexArray::bind() const {
    //auto gl{gladGetGLContext()};
    glBindVertexArray(vertexArrayId_);
  }

  void OpenGLVertexArray::unbind() const {
    //auto gl{gladGetGLContext()};
    glBindVertexArray(0);
  }

  void OpenGLVertexArray::addVertexBuffer(Shared<VertexBuffer> vertexBuffer) {
    FGE_ASSERT_ENG(vertexBuffer->layout().elements().size(), "Vertex buffer has no layout!");

    //auto gl{gladGetGLContext()};
    glBindVertexArray(vertexArrayId_);

    vertexBuffer->bind();
    uint32_t i{0};
    for (const auto& element : vertexBuffer->layout()) {
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, 
        element.componentCount(),
        shaderDataToOpenGLBaseType(element.type), 
        element.normalized, 
        vertexBuffer->layout().stride(), // size of an entire vertex including all attr
        (const void*)static_cast<uint64_t>(element.offset) // offset of this attr in the vertex
      );
      ++i;
    }
    vertexBuffers_.push_back(vertexBuffer);

    glBindVertexArray(0);
    vertexBuffer->unbind();
  }

  void OpenGLVertexArray::setIndexBuffer(Shared<IndexBuffer> indexBuffer) {
    //auto gl{gladGetGLContext()};
    glBindVertexArray(vertexArrayId_);

    indexBuffer->bind();
    indexBuffer_ = indexBuffer;

    glBindVertexArray(0);
    indexBuffer->unbind();
  }
}