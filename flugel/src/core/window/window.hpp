#pragma once

#include "core/color/color.hpp"
#include "core/events/notifier.hpp"
#include "core/events/window_event.hpp"
#include "core/events/mouse_event.hpp"
#include "core/events/keyboard_event.hpp"

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

    void makeContextCurrent();
    void processInput();
    void swapBuffers();

    int32_t xPos() const { return data_.xPos; }
    int32_t yPos() const { return data_.yPos; }
    void setPos(int32_t xPos, int32_t yPos);

    uint32_t width() const { return data_.width; }
    uint32_t height() const { return data_.height; }

    bool isVSync() const { return data_.vSync; }
    void setVSync(bool enabled);

    // Window Events
    Notifier<WindowCloseEvent>& windowCloseNotifier() { return data_.windowCloseNotifier; }
    Notifier<WindowResizeEvent>& windowResizeNotifier() { return data_.windowResizeNotifier; }
    Notifier<WindowMovedEvent>& windowMovedNotifier() { return data_.windowMovedNotifier; }
    // Mouse Events
    Notifier<MousePressedEvent>& mousePressedNotifier() { return data_.mousePressedNotifier; }
    Notifier<MouseReleasedEvent>& mouseReleasedNotifier() { return data_.mouseReleasedNotifier; }
    Notifier<MouseMovedEvent>& mouseMovedNotifier() { return data_.mouseMovedNotifier; }
    Notifier<MouseScrolledEvent>& mouseScrolledNotifier() { return data_.mouseScrolledNotifier; }
    // Mouse Events
    Notifier<KeyPressedEvent>& keyPressedNotifier() { return data_.keyPressedNotifier; }
    Notifier<KeyReleasedEvent>& keyReleasedNotifier() { return data_.keyReleasedNotifier; }
    
  private:
    struct WindowData {
      std::string title;
      int32_t xPos, yPos;
      uint32_t width, height;
      bool vSync;

      // Window Events
      Notifier<WindowCloseEvent> windowCloseNotifier{};
      Notifier<WindowResizeEvent> windowResizeNotifier{};
      Notifier<WindowMovedEvent> windowMovedNotifier{};
      // Mouse Events
      Notifier<MousePressedEvent> mousePressedNotifier{};
      Notifier<MouseReleasedEvent> mouseReleasedNotifier{};
      Notifier<MouseMovedEvent> mouseMovedNotifier{};
      Notifier<MouseScrolledEvent> mouseScrolledNotifier{};
      // Mouse Events
      Notifier<KeyPressedEvent> keyPressedNotifier{};
      Notifier<KeyReleasedEvent> keyReleasedNotifier{};
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