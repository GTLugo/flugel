#include "opengl_vertex_array.hpp"

#include <glad/gl.h>

namespace fge {
  static GLenum shaderDataToOpenGLBaseType(BufferElement::Type type) {
    switch (type) {
      case BufferElement::Type::Bool:   { return GL_BOOL; }
      case BufferElement::Type::Int:    { return GL_INT; }
      case BufferElement::Type::Int2:   { return GL_INT; }
      case BufferElement::Type::Int3:   { return GL_INT; }
      case BufferElement::Type::Int4:   { return GL_INT; }
      case BufferElement::Type::Float:  { return GL_FLOAT; }
      case BufferElement::Type::Float2: { return GL_FLOAT; }
      case BufferElement::Type::Float3: { return GL_FLOAT; }
      case BufferElement::Type::Float4: { return GL_FLOAT; }
      case BufferElement::Type::Mat3:   { return GL_FLOAT; }
      case BufferElement::Type::Mat4:   { return GL_FLOAT; }
      default:                     { return 0; }
    }
  }

  OpenGLVertexArray::~OpenGLVertexArray() {
    auto gl{gladGetGLContext()};
    
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
    FGE_ASSERT_ENG(!vertexBuffer->layout().elements().empty(), "Vertex buffer has no layout!");

    //auto gl{gladGetGLContext()};
    glBindVertexArray(vertexArrayId_);

    vertexBuffer->bind();
    u32 i{0};
    for (const auto& element : vertexBuffer->layout()) {
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, 
        element.componentCount,
        shaderDataToOpenGLBaseType(element.type), 
        element.normalized, 
        vertexBuffer->layout().stride(), // size of an entire vertex including all attr
        (const void*)static_cast<u64>(element.offset) // offset of this attr in the vertex
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