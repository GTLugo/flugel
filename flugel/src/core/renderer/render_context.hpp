#pragma once

namespace fge {
  enum class RenderAPI {
    OpenGL,
    Vulkan,
    D3D11,
  };

  class RenderContext {
  public:
    virtual void init() = 0;
    
    virtual void setCurrent(bool isCurrent) = 0;
    virtual void swapBuffers() = 0;
  private:
  };
}