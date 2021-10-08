#pragma once

#include "window.hpp"
#include "util/color/color.hpp"
#include "core/callbacks/events/event.hpp"

#include <GLFW/glfw3.h>

namespace Flugel {
  class FLUGEL_API GlfwWindow : public Window {
  public:
    GlfwWindow(const WindowProperties& props);
    virtual ~GlfwWindow();
    
    virtual void pollEvents() override;
    virtual void render() override;
    
    virtual void* nativeWindow() override { return glfwWindow_; }
    virtual void dragWindow(double cursorOffsetX, double cursorOffsetY);
    virtual void setPos(double xPos, double yPos) override;
    virtual void setVSync(bool enabled) override;
    virtual void setFullscreen(bool enabled) override;
    virtual void setContextCurrent(bool current) override;
    
  private:
    GLFWwindow* glfwWindow_;
    const GLFWvidmode* vidMode_;

    Color clearColor_{0x2E3440FF};
    
    void init(bool shouldUseDefaultDecor);
    void setCallbacks();
    void shutdown();
  };
}