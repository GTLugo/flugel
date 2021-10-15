#pragma once

#include "core/renderer/render_context.hpp"
#include "util/color/color.hpp"

struct GLFWwindow;

namespace fge {
  class OpenGLContext : public RenderContext {
  public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void init() override;

    virtual void setCurrent(bool isCurrent) override;
    virtual void swapBuffers() override;
  private:
    GLFWwindow* windowHandle_;

    Color clearColor_{0x2D2A2AFF};
  };
}