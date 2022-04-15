#pragma once

namespace ff {
  class RenderContext {
  public:
    virtual void* commandBuffer() = 0; // Vulkan
    virtual void* pipeline() = 0; // Vulkan
    virtual void* nativeContext() = 0; // OpenGL
    virtual void setCurrent(bool isCurrent) = 0;
    virtual void swapBuffers() = 0;
  };
}