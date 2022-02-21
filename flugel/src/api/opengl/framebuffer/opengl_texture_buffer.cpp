//
// Created by galex on 2/20/2022.
//

#include "opengl_texture_buffer.hpp"

#include <glad/gl.h>

namespace fge {
  OpenGLTextureBuffer::OpenGLTextureBuffer(TextureBuffer::Format format, i32 width, i32 height, void* data) {
    glGenTextures(1, &textureId_);
    bind();
    i32 glFormat{};
    switch (format) {
      case Format::None:
        glFormat = 0;
        break;
      case Format::RGB:
        glFormat = GL_RGB;
        break;
      default: FGE_ASSERT_ENG(false, "Unsupported texture buffer format!");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unbind();
  }

  void OpenGLTextureBuffer::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureId_);
  }

  void OpenGLTextureBuffer::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}