#pragma once

#include "core/window/window.hpp"
#include "core/callbacks/events/event.hpp"
#include "util/color/color.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  class GlfwWindow : public Window {
  public:
    GlfwWindow(const WindowProperties& props);
    virtual ~GlfwWindow();
    
    virtual void pollEvents() override;
    virtual void render() override;
    
    virtual void* nativeWindow() override { return glfwWindow_; }
    virtual void dragWindow(vector2_t windowCursorOffset);

    virtual void setIcon(uint8_t* image, int32_t width, int32_t height) override;
    virtual void setPos(double xPos, double yPos) override;
    virtual void setVSync(bool enabled) override;
    virtual void setFullscreen(bool enabled) override;
    virtual void setContextCurrent(bool current) override;
    
  private:
    GLFWwindow* glfwWindow_;
    const GLFWvidmode* vidMode_;

    GLFWimage icons_[1];
    Color clearColor_{0x2D2A2AFF};
    
    void init();
    void setCallbacks();
    void shutdown();
  };
}