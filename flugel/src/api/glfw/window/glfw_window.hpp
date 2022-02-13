#pragma once

#include "core/window/window.hpp"
#include "core/callbacks/events/event.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  class GlfwWindow : public Window {
  public:
    GlfwWindow(const WindowProperties& props);
    virtual ~GlfwWindow();
    
    virtual void pollEvents() override;
    
    virtual void* nativeWindow() override { return glfwWindow_; }
    virtual void dragWindow(ivec2 windowCursorOffset);

    virtual void setIcon(u8* image, i32 width, i32 height) override;
    virtual void setPos(i32 xPos, i32 yPos) override;
    virtual void setVSync(bool enabled) override;
    virtual void setFullscreen(bool enabled) override;
    //virtual void setContextCurrent(bool isCurrent) override;
    
  private:
    GLFWwindow* glfwWindow_;
    const GLFWvidmode* vidMode_;

    GLFWimage icons_[1];
    
    void init();
    void setCallbacks();
    void shutdown();
  };
}