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
    bool fullScreen;
    bool borderless;
    bool shouldUseDefaultDecor;

    WindowProperties(const std::string& title = "FLUGEL ENGINE",
                     uint32_t width = 800,
                     uint32_t height = 450,
                     bool vSync = true,
                     bool fullScreen = false,
                     bool borderless = false,
                     bool shouldUseDefaultDecor = true)
      : title{title}, 
        width{width}, 
        height{height}, 
        vSync{vSync}, 
        fullScreen{fullScreen}, 
        borderless{borderless}, 
        shouldUseDefaultDecor{shouldUseDefaultDecor} {}
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

    inline void setContextCurrent(bool current);
    void processInput();
    void swapBuffers();

    UniqueGlfwWindow& window() { return glfwWindow_; }
    int32_t xPos() const { return data_.xPos; }
    int32_t yPos() const { return data_.yPos; }
    uint32_t width() const { return data_.width; }
    uint32_t height() const { return data_.height; }
    bool isVSync() const { return data_.vSync; }
    bool isFullscreen() const { return data_.fullScreen; }

    void setPos(int32_t xPos, int32_t yPos);
    void setVSync(bool enabled);
    void setFullscreen(bool enabled);
    void setEventCallback(const EventCallbackFn& callback) { data_.eventCallback = callback; }
    
  private:
    struct WindowData {
      std::string title;
      int32_t xPos, yPos;
      int32_t xPosBeforeFullscreen, yPosBeforeFullscreen;
      uint32_t width, height;
      uint32_t widthBeforeFullscreen, heightBeforeFullscreen;
      bool vSync;
      bool fullScreen;
      bool borderless;
      EventCallbackFn eventCallback;

      WindowData(const WindowProperties& props) 
        : title{props.title},
          xPos{50},
          yPos{50},
          width{props.width}, 
          height{props.height}, 
          vSync{props.vSync},
          fullScreen{props.fullScreen},
          borderless{props.borderless} {}
    };

    static bool isGlfwInitialized_;
    WindowData data_;
    UniqueGlfwWindow glfwWindow_;
    const GLFWvidmode* vidMode_;

    Color clearColor_{0x2E3440FF};
  private:
    void init(bool shouldUseDefaultDecor);
    void setCallbacks();
    void shutdown();
  };
}