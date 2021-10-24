#pragma once

#include "core/renderer/context.hpp"

struct GLFWwindow;
struct GladGLContext;

namespace fge {
  class OpenGLContext : public RenderContext {
  public:
    OpenGLContext(GLFWwindow* windowHandle);
    ~OpenGLContext();

    //virtual void* nativeContext() override { return context_; }
    virtual void setCurrent(bool isCurrent) override;
    virtual void swapBuffers() override;
  private:
    GLFWwindow* windowHandle_;
    //GladGLContext* context_;

    virtual void init() override;
  };
}