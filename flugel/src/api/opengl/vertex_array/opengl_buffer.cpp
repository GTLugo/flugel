#include "opengl_buffer.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace fge {

  // VERTEX BUFFER --------------------------- //

  OpenGLVertexBuffer::OpenGLVertexBuffer(float* verts, u32 bitSize) {
    //auto gl{gladGetGLContext()};
    glCreateBuffers(1, &bufferId_);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId_);
    glBufferData(GL_ARRAY_BUFFER, bitSize, verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    //auto gl{gladGetGLContext()};
    glDeleteBuffers(1, &bufferId_);
  }

  void OpenGLVertexBuffer::bind() const {
    //auto gl{gladGetGLContext()};
    glBindBuffer(GL_ARRAY_BUFFER, bufferId_);
  }

  void OpenGLVertexBuffer::unbind() const {
    //auto gl{gladGetGLContext()};
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  // INDEX BUFFER --------------------------- //

  OpenGLIndexBuffer::OpenGLIndexBuffer(u32* indices, u32 count)
    : count_{count} {
    //auto gl{gladGetGLContext()};
    glCreateBuffers(1, &bufferId_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(indices[0]), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    //auto gl{gladGetGLContext()};
    glDeleteBuffers(1, &bufferId_);
  }

  void OpenGLIndexBuffer::bind() const {
    //auto gl{gladGetGLContext()};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId_);
  }

  void OpenGLIndexBuffer::unbind() const {
    //auto gl{gladGetGLContext()};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}