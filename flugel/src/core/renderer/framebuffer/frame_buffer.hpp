//
// Created by galex on 2/20/2022.
//

#pragma once


namespace fge {
  class FGE_API FrameBuffer {
  public:
    virtual ~FrameBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static Shared<FrameBuffer> create();
  };
}

