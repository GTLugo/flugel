#pragma once

#include "core/renderer/render_context.hpp"

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
  };
}