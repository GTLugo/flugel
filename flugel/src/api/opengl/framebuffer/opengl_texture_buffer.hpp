//
// Created by galex on 2/20/2022.
//

#pragma once

#include "core/renderer/framebuffer/texture_buffer.hpp"

namespace fge {
  class OpenGLTextureBuffer : public TextureBuffer {
  public:
    OpenGLTextureBuffer(Format format, i32 width, i32 height, void* data);
    ~OpenGLTextureBuffer() override = default;

    void bind() const final;
    void unbind() const final;
  private:
    u32 textureId_{};
  };
}

