//
// Created by galex on 2/20/2022.
//

#include "opengl_texture_buffer.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace fge {
  OpenGLTextureBuffer::OpenGLTextureBuffer(TextureBuffer::Format format, i32 width, i32 height, void* data) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->GenTextures(1, &textureId_);
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
    gl->TexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);

    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unbind();
  }

  OpenGLTextureBuffer::~OpenGLTextureBuffer() {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->DeleteTextures(1, &textureId_);
  }

  void OpenGLTextureBuffer::bind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindTexture(GL_TEXTURE_2D, textureId_);
  }

  void OpenGLTextureBuffer::unbind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindTexture(GL_TEXTURE_2D, 0);
  }

  void* OpenGLTextureBuffer::handle() const {
    return reinterpret_cast<void*>(textureId_);
  }
}