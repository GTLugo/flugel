#pragma once

#include "flugel/window.hpp"

#include <GLFW/glfw3.h>

namespace Flugel {
  class WindowsWindow : public Window {
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();
    
    void onUpdate() override;

    inline uint32_t getWidth() const override { return data_.width; }
    inline uint32_t getHeight() const override { return data_.height; }
    
    // Window attributes
    inline void setEventCallback(const EventCallbackFn& callback) override {
      data_.eventCallback = callback;
    }
    void setVsync(bool enabled) override;
    bool isVsync() const override { return data_.vsync; }

  private:
    struct WindowData {
      std::string title;
      uint32_t width, height;
      bool vsync;
      EventCallbackFn eventCallback;
    };

    GLFWwindow* glfwWindow_;

    WindowData data_;
  private:
    virtual void init(const WindowProps& props);
    virtual void shut();
  };
}