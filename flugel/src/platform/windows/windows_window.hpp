#pragma once

#include "flugel/window.hpp"

#include <GLFW/glfw3.h>

namespace Flugel {
  class WindowsWindow : public Window {
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();
    
    void update() override;
    
    // Window attributes
    void setVsync(bool enabled) override;
  private:
    GLFWwindow* glfwWindow_;
  private:
    virtual void init(const WindowProps& props);
    virtual void shut();
    virtual void setGlfwCallbacks();
  };
}