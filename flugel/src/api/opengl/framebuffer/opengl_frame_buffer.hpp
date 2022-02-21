//
// Created by galex on 2/20/2022.
//

#pragma once

#include "core/renderer/framebuffer/frame_buffer.hpp"

namespace fge {
  class OpenGLFrameBuffer : public FrameBuffer {
  public:
    OpenGLFrameBuffer();
    ~OpenGLFrameBuffer() override;

    void bind() const final;
    void unbind() const final;
  private:
    u32 frameBufferId_{};
  };
}

