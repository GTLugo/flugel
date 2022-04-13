#include "opengl_vertex_array.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace ff {
  static GLenum shaderDataToOpenGLBaseType(VertexAttributeBase::Type type) {
    switch (type) {
      case VertexAttributeBase::Type::Bool:   { return GL_BOOL; }
      case VertexAttributeBase::Type::Int:    { return GL_INT; }
      case VertexAttributeBase::Type::Int2:   { return GL_INT; }
      case VertexAttributeBase::Type::Int3:   { return GL_INT; }
      case VertexAttributeBase::Type::Int4:   { return GL_INT; }
      case VertexAttributeBase::Type::Float:  { return GL_FLOAT; }
      case VertexAttributeBase::Type::Float2: { return GL_FLOAT; }
      case VertexAttributeBase::Type::Float3: { return GL_FLOAT; }
      case VertexAttributeBase::Type::Float4: { return GL_FLOAT; }
      case VertexAttributeBase::Type::Mat3:   { return GL_FLOAT; }
      case VertexAttributeBase::Type::Mat4:   { return GL_FLOAT; }
      default:                     { return 0; }
    }
  }

  OpenGLVertexArray::~OpenGLVertexArray() {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    
    gl->DeleteVertexArrays(1, &vertexArrayId_);
  }

  OpenGLVertexArray::OpenGLVertexArray(Shared<VertexBuffer> vertexBuffer, Shared<IndexBuffer> indexBuffer) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};

    gl->CreateVertexArrays(1, &vertexArrayId_);
    addVertexBuffer(vertexBuffer);
    setIndexBuffer(indexBuffer);
  }

  void OpenGLVertexArray::bind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindVertexArray(vertexArrayId_);
  }

  void OpenGLVertexArray::unbind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindVertexArray(0);
  }

  void OpenGLVertexArray::addVertexBuffer(Shared<VertexBuffer> vertexBuffer) {
    FF_ASSERT_E(!vertexBuffer->layout().elements().empty(), "Vertex buffer has no layout!");
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};

    //auto gl{gladGetGLContext()};
    gl->BindVertexArray(vertexArrayId_);

    vertexBuffer->bind();
    u32 i{0};
    for (const auto& element : vertexBuffer->layout()) {
      gl->EnableVertexAttribArray(i);
      gl->VertexAttribPointer(i,
        element.componentCount,
        shaderDataToOpenGLBaseType(element.type),
        element.normalized,
        vertexBuffer->layout().stride(), // size of an entire vertex including all attr
        (const void*)static_cast<u64>(element.offset) // offset of this attr in the vertex
      );
      ++i;
    }
    vertexBuffers_.push_back(vertexBuffer);

    gl->BindVertexArray(0);
    vertexBuffer->unbind();
  }

  void OpenGLVertexArray::setIndexBuffer(Shared<IndexBuffer> indexBuffer) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindVertexArray(vertexArrayId_);

    indexBuffer->bind();
    indexBuffer_ = indexBuffer;

    gl->BindVertexArray(0);
    indexBuffer->unbind();
  }
}