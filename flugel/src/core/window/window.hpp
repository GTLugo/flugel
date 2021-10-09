#pragma once

#include "core/callbacks/events/event.hpp"

namespace fge {
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

  class FGE_API Window {
  protected:
    using EventCallbackFn = std::function<void(Event&)>;
  public:
    virtual ~Window() = default;
    
    virtual void pollEvents() = 0;
    virtual void render() = 0;
    
    virtual void* nativeWindow() = 0;
    virtual void dragWindow(vector2_t windowCursorOffset) = 0;

    virtual void setIcon(uint8_t* image, int32_t width, int32_t height) = 0;
    virtual void setPos(double xPos, double yPos) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual void setFullscreen(bool enabled) = 0;
    virtual void setContextCurrent(bool current) = 0;

    ivector2_t pos() const { return data_.windowPos; }
    uvector2_t dims() const { return data_.windowDims; }
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
      ivector2_t windowPos, posBeforeFullscreen;
      uvector2_t windowDims, dimsBeforeFullscreen;
      vector2_t cursorPos, cursorPosOld, cursorDelta;
      bool vSync;
      bool fullScreen;
      bool borderless;
      bool customDecor;
      EventCallbackFn eventCallback;

      WindowState(const WindowProperties& props) 
        : title{props.title},
          windowPos{69, 69}, posBeforeFullscreen{windowPos},
          windowDims{props.width, props.height}, dimsBeforeFullscreen{windowDims}, 
          vSync{props.vSync},
          fullScreen{props.fullScreen},
          borderless{props.borderless},
          customDecor{props.customDecor} {}
    };

    WindowState data_;
  };
}