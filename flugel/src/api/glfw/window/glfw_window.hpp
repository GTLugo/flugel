#pragma once

#include "core/window/window.hpp"
#include "core/callbacks/events/event.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  class GlfwWindow : public Window {
  public:
    explicit GlfwWindow(const WindowProperties& props);
    ~GlfwWindow() override;
    
    void pollEvents() override;
    
    void* nativeWindow() override { return glfwWindow_; }
    void dragWindow(ivec2 windowCursorOffset) override;

    void setIcon(u8* image, i32 width, i32 height) override;
    void setPos(i32 xPos, i32 yPos) override;
    void setVSync(bool enabled) override;
    void setFullscreen(bool enabled) override;
    //virtual void setContextCurrent(bool isCurrent) override;
    
  private:
    GLFWwindow* glfwWindow_{};
    const GLFWvidmode* vidMode_{};

    GLFWimage icons_[1]{};
    
    void init();
    void setCallbacks();
    void shutdown();
  };
}