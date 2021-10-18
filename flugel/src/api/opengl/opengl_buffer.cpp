#include "opengl_buffer.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace fge {

  // VERTEX BUFFER --------------------------- //

  OpenGLVertexBuffer::OpenGLVertexBuffer(float* verts, uint32_t bitSize) {
    auto gl{gladGetGLContext()};
    gl->CreateBuffers(1, &bufferId_);
    bind();
    gl->BufferData(GL_ARRAY_BUFFER, bitSize, verts, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    auto gl{gladGetGLContext()};
    gl->DeleteBuffers(1, &bufferId_);
  }

  void OpenGLVertexBuffer::bind() const {
    auto gl{gladGetGLContext()};
    gl->BindBuffer(GL_ARRAY_BUFFER, bufferId_);
  }

  void OpenGLVertexBuffer::unbind() const {
    auto gl{gladGetGLContext()};
    gl->BindBuffer(GL_ARRAY_BUFFER, 0);
  }

  // INDEX BUFFER --------------------------- //

  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    : count_{count} {
    auto gl{gladGetGLContext()};
    gl->CreateBuffers(1, &bufferId_);
    bind();
    gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(indices[0]), indices, GL_STATIC_DRAW);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    auto gl{gladGetGLContext()};
    gl->DeleteBuffers(1, &bufferId_);
  }

  void OpenGLIndexBuffer::bind() const {
    auto gl{gladGetGLContext()};
    gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId_);
  }

  void OpenGLIndexBuffer::unbind() const {
    auto gl{gladGetGLContext()};
    gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}