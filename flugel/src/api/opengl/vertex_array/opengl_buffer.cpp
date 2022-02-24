#include "opengl_buffer.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace fge {

  // VERTEX BUFFER --------------------------- //

  OpenGLVertexBuffer::OpenGLVertexBuffer(float* verts, u32 bitSize) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->CreateBuffers(1, &bufferId_);
    gl->BindBuffer(GL_ARRAY_BUFFER, bufferId_);
    gl->BufferData(GL_ARRAY_BUFFER, bitSize, verts, GL_STATIC_DRAW);
    gl->BindBuffer(GL_ARRAY_BUFFER, 0);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->DeleteBuffers(1, &bufferId_);
  }

  void OpenGLVertexBuffer::bind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindBuffer(GL_ARRAY_BUFFER, bufferId_);
  }

  void OpenGLVertexBuffer::unbind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindBuffer(GL_ARRAY_BUFFER, 0);
  }

  // INDEX BUFFER --------------------------- //

  OpenGLIndexBuffer::OpenGLIndexBuffer(u32* indices, u32 count)
    : count_{count} {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->CreateBuffers(1, &bufferId_);
    gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId_);
    gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(indices[0]), indices, GL_STATIC_DRAW);
    gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->DeleteBuffers(1, &bufferId_);
  }

  void OpenGLIndexBuffer::bind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId_);
  }

  void OpenGLIndexBuffer::unbind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}