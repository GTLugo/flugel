#pragma once

#include "core/events/notifier.hpp"
#include "core/events/window_event.hpp"
#include "core/color/color.hpp"

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

    void processInput();
    void swapBuffers();

    uint32_t width() const { return data_.width; }
    uint32_t height() const { return data_.height; }
    bool isVSync() const { return data_.vSync; }
    void setVSync(bool enabled);
    Notifier<WindowCloseEvent>& closeNotifier() { return data_.closeNotifier; }
    
  private:
    struct WindowData {
      std::string title;
      uint32_t width, height;
      bool vSync;

      Notifier<WindowCloseEvent> closeNotifier{};
      WindowData(const WindowProperties& props) 
        : title{props.title}, width{props.width}, height{props.height}, vSync{props.vSync} {}
    };

    static bool isGlfwInitialized_;
    WindowData data_;
    UniqueGlfwWindow glfwWindow_;

    Color clearColor_{0x2E3440FF};
  private:
    void init();
    void shutdown();
  };
}