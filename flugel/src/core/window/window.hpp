#pragma once

#include "util/color/color.hpp"
#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"

#include <GLFW/glfw3.h>

namespace Flugel {
  struct WindowProperties {
    std::string title;
    uint32_t width, height;
    bool vSync;

    WindowProperties(const std::string& title = "FLUGEL ENGINE",
                     uint32_t width = 800,
                     uint32_t height = 450,
                     bool vSync = true)
      : title{title}, width{width}, height{height}, vSync{vSync} {}
  };

  class FLUGEL_API Window {
    using EventCallbackFn = std::function<void(Event&)>;
  public:
    struct GLFWwindowDelete {
      void operator()(GLFWwindow* ptr) {
        glfwDestroyWindow(ptr);
      }
    };

    using UniqueGlfwWindow = Unique<GLFWwindow, GLFWwindowDelete>;

  public:
    Window(const WindowProperties& props = {});
    virtual ~Window();

    void makeContextCurrent();
    void makeContextNonCurrent();
    void processInput();
    void swapBuffers();

    UniqueGlfwWindow& window() { return glfwWindow_; }
    int32_t xPos() const { return data_.xPos; }
    int32_t yPos() const { return data_.yPos; }
    uint32_t width() const { return data_.width; }
    uint32_t height() const { return data_.height; }
    bool isVSync() const { return data_.vSync; }

    void setPos(int32_t xPos, int32_t yPos);
    void setVSync(bool enabled);
    void setEventCallback(const EventCallbackFn& callback) { data_.eventCallback = callback; }
    
  private:
    struct WindowData {
      std::string title;
      int32_t xPos, yPos;
      uint32_t width, height;
      bool vSync;
      EventCallbackFn eventCallback;

      WindowData(const WindowProperties& props) 
        : title{props.title}, width{props.width}, height{props.height}, vSync{props.vSync} {}
    };

    static bool isGlfwInitialized_;
    WindowData data_;
    UniqueGlfwWindow glfwWindow_;

    Color clearColor_{0x2E3440FF};
  private:
    void init();
    void setCallbacks();
    void shutdown();
  };
}