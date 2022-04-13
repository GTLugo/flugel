#pragma once

#include "core/renderer/context.hpp"

struct GLFWwindow;
struct GladGLContext;

namespace ff {
  class OpenGLContext : public RenderContext {
  public:
    explicit OpenGLContext(GLFWwindow* windowHandle);
    ~OpenGLContext();

    virtual void* nativeContext() override { return context_; }
    void setCurrent(bool isCurrent) final;
    void swapBuffers() final;
  private:
    GLFWwindow* windowHandle_;
    GladGLContext* context_;
  };
}