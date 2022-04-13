//
// Created by galex on 2/20/2022.
//

#pragma once

#include "texture_buffer.hpp"


namespace ff {
  class FrameBuffer {
  public:
    virtual ~FrameBuffer() = default;

    static Shared<FrameBuffer> create(TextureBuffer::Format format, i32 width, i32 height, void* data);
    static Shared<FrameBuffer> create(const Shared<TextureBuffer>& textureBuffer);

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    void attachTextureBuffer(Shared<TextureBuffer>& textureBuffer) { textureBuffer_ = textureBuffer; }
    Shared<TextureBuffer>& textureBuffer() { return textureBuffer_; }
  protected:
    Shared<TextureBuffer> textureBuffer_;
  };
}

