//
// Created by galex on 2/20/2022.
//

#include "opengl_frame_buffer.hpp"

#include <glad/gl.h>

namespace fge {
  OpenGLFrameBuffer::OpenGLFrameBuffer() {
    glGenFramebuffers(1, &frameBufferId_);

    FGE_ASSERT_ENG(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Error setting up frame buffer!");
  }

  OpenGLFrameBuffer::~OpenGLFrameBuffer() {
    glDeleteFramebuffers(1, &frameBufferId_);
  }

  void OpenGLFrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId_);
  }

  void OpenGLFrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}