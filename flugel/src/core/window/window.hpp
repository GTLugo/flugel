#pragma once

#include "core/callbacks/events/event.hpp"

namespace Flugel {
  struct WindowProperties {
    std::string title;
    uint32_t width, height;
    bool vSync;
    bool fullScreen;
    bool borderless;
    bool customDecor;

    WindowProperties(const std::string& title = "FLUGEL ENGINE",
                     uint32_t width = 800,
                     uint32_t height = 450,
                     bool vSync = true,
                     bool fullScreen = false,
                     bool borderless = false,
                     bool customDecor = false)
      : title{title}, 
        width{width}, 
        height{height}, 
        vSync{vSync}, 
        fullScreen{fullScreen}, 
        borderless{borderless}, 
        customDecor{customDecor} {}
  };

  class FLUGEL_API Window {
  protected:
    using EventCallbackFn = std::function<void(Event&)>;
  public:
    virtual ~Window() = default;
    
    virtual void pollEvents() = 0;
    virtual void render() = 0;
    
    virtual void* nativeWindow() = 0;
    virtual void dragWindow(double cursorOffsetX, double cursorOffsetY) = 0;

    virtual void setIcon(uint8_t* image, int32_t width, int32_t height) = 0;
    virtual void setPos(double xPos, double yPos) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual void setFullscreen(bool enabled) = 0;
    virtual void setContextCurrent(bool current) = 0;

    int32_t xPos() const { return data_.xPos; }
    int32_t yPos() const { return data_.yPos; }
    uint32_t width() const { return data_.width; }
    uint32_t height() const { return data_.height; }
    bool isVSync() const { return data_.vSync; }
    bool isFullscreen() const { return data_.fullScreen; }
    bool isUsingCustomDecor() const { return data_.customDecor; }
    void setEventCallback(const EventCallbackFn& callback) { data_.eventCallback = callback; }
    
    static Unique<Window> create(const WindowProperties& props = {});
  protected:
    Window(const WindowProperties& props)
      : data_{props} {}

    struct WindowState {
      std::string title;
      int32_t xPos, yPos;
      int32_t xPosBeforeFullscreen, yPosBeforeFullscreen;
      uint32_t width, height;
      uint32_t widthBeforeFullscreen, heightBeforeFullscreen;
      glm::vec2 cursorPos, cursorPosOld, cursorDelta;
      bool vSync;
      bool fullScreen;
      bool borderless;
      bool customDecor;
      EventCallbackFn eventCallback;

      WindowState(const WindowProperties& props) 
        : title{props.title},
          xPos{69},
          yPos{69},
          width{props.width}, 
          height{props.height}, 
          vSync{props.vSync},
          fullScreen{props.fullScreen},
          borderless{props.borderless},
          customDecor{props.customDecor} {}
    };

    WindowState data_;
  };
}