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

  OpenGLVertexArray::OpenGLVertexArray(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer) {
    auto gl{gladGetGLContext()};

    gl->CreateVertexArrays(1, &vertexArrayId_);
    addVertexBuffer(vertexBuffer);
    setIndexBuffer(indexBuffer);
  }

  void OpenGLVertexArray::bind() const {
    auto gl{gladGetGLContext()};
    gl->BindVertexArray(vertexArrayId_);
  }

  void OpenGLVertexArray::unbind() const {
    auto gl{gladGetGLContext()};
    gl->BindVertexArray(0);
  }

  void OpenGLVertexArray::addVertexBuffer(Shared<VertexBuffer> vertexBuffer) {
    auto gl{gladGetGLContext()};
    gl->BindVertexArray(vertexArrayId_);

    vertexBuffer->bind();
    uint32_t i{0};
    for (const auto& element : vertexBuffer->layout()) {
      gl->EnableVertexAttribArray(i);
      gl->VertexAttribPointer(i, 
        element.componentCount(),
        shaderDataToOpenGLBaseType(element.type), 
        element.normalized, 
        vertexBuffer->layout().stride(), // size of an entire vertex including all attr
        (const void*)static_cast<uint64_t>(element.offset) // offset of this attr in the vertex
      );
      ++i;
    }
    vertexBuffers_.push_back(vertexBuffer);

    gl->BindVertexArray(0);
  }

  void OpenGLVertexArray::setIndexBuffer(Shared<IndexBuffer> indexBuffer) {
    auto gl{gladGetGLContext()};
    gl->BindVertexArray(vertexArrayId_);
    
    indexBuffer->bind();
    indexBuffer_ = indexBuffer;

    gl->BindVertexArray(0);
  }
}