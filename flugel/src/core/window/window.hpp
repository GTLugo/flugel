#pragma once

#include "core/renderer/renderer.hpp"
#include "core/renderer/context.hpp"
#include "core/callbacks/events/event.hpp"

namespace fge {
  struct WindowProperties {
    std::string title;
    uint32_t width, height;
    Renderer::API renderApi;
    bool vSync;
    bool fullScreen;
    bool borderless;
    bool customDecor;

    WindowProperties(const std::string& title = "FLUGEL ENGINE",
                     uint32_t width = 800,
                     uint32_t height = 450,
                     Renderer::API renderApi = Renderer::API::OpenGL,
                     bool vSync = true,
                     bool fullScreen = false,
                     bool borderless = false,
                     bool customDecor = false)
      : title{title}, 
        width{width}, 
        height{height},
        renderApi{renderApi},
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
    
    virtual RenderContext& context() { return *context_; }
    virtual void* nativeWindow() = 0;
    virtual void dragWindow(vector2_t windowCursorOffset) = 0;

    virtual void setIcon(uint8_t* image, i32 width, i32 height) = 0;
    virtual void setPos(double xPos, double yPos) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual void setFullscreen(bool enabled) = 0;
    //virtual void setContextCurrent(bool isCurrent) = 0;

    ivector2_t pos() const { return data_.windowPos; }
    uvector2_t dims() const { return data_.windowDims; }
    bool isVSync() const { return data_.vSync; }
    bool isFullscreen() const { return data_.fullScreen; }
    bool isUsingCustomDecor() const { return data_.customDecor; }
    void setEventCallback(const EventCallbackFn& callback) { data_.eventCallback = callback; }
    
    static Unique<Window> create(const WindowProperties& props = {});
  protected:
    Window(const WindowProperties& props)
      : data_{props} {
      Renderer::setApi(props.renderApi);
    }

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
    Unique<Renderer> renderer_;
    Unique<RenderContext> context_;
  };
}