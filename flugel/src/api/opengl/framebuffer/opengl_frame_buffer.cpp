//
// Created by galex on 2/20/2022.
//

#include "opengl_frame_buffer.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace fge {
  OpenGLFrameBuffer::OpenGLFrameBuffer(TextureBuffer::Format format, i32 width, i32 height, void* data) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->GenFramebuffers(1, &frameBufferId_);
    textureBuffer_ = TextureBuffer::create(format, width, height, data);
    bind();
    gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reinterpret_cast<u32>(textureBuffer_->handle()), 0);
    FGE_ASSERT_ENG(gl->CheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Error setting up frame buffer!");
    unbind();
  }

  OpenGLFrameBuffer::OpenGLFrameBuffer(const Shared<TextureBuffer>& textureBuffer) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->GenFramebuffers(1, &frameBufferId_);
    textureBuffer_ = textureBuffer;
    bind();
    gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reinterpret_cast<u32>(textureBuffer_->handle()), 0);
    FGE_ASSERT_ENG(gl->CheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Error setting up frame buffer!");
    unbind();
  }

  OpenGLFrameBuffer::~OpenGLFrameBuffer() {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->DeleteFramebuffers(1, &frameBufferId_);
  }

  void OpenGLFrameBuffer::bind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindFramebuffer(GL_FRAMEBUFFER, frameBufferId_);
  }

  void OpenGLFrameBuffer::unbind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}