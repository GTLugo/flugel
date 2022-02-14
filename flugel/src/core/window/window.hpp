#pragma once

#include <utility>

#include "core/renderer/renderer.hpp"
#include "core/renderer/context.hpp"
#include "core/callbacks/events/event.hpp"

namespace fge {
  struct WindowProperties {
    std::string title;
    i32 width, height;
    Renderer::API renderApi;
    bool vSync;
    bool fullScreen;
    bool borderless;
    bool customDecor;

    WindowProperties(std::string title = "FLUGEL ENGINE",
                     i32 width = 800,
                     i32 height = 450,
                     Renderer::API renderApi = Renderer::API::OpenGL,
                     bool vSync = true,
                     bool fullScreen = false,
                     bool borderless = false,
                     bool customDecor = false)
      : title{std::move(title)},
        width{width},
        height{height},
        renderApi{renderApi},
        vSync{vSync},
        fullScreen{fullScreen},
        borderless{borderless},
        customDecor{customDecor} {}

    WindowProperties(const WindowProperties& props) = default;
  };

  class FGE_API Window {
  protected:
    using EventCallbackFn = std::function<void(Event&)>;
  public:
    virtual ~Window() = default;
    
    virtual void pollEvents() = 0;
    
    virtual RenderContext& context() { return *context_; }
    virtual void* nativeWindow() = 0;
    virtual void dragWindow(ivec2 windowCursorOffset) = 0;

    virtual void setIcon(u8* image, i32 width, i32 height) = 0;
    virtual void setPos(i32 xPos, i32 yPos) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual void setFullscreen(bool enabled) = 0;
    //virtual void setContextCurrent(bool isCurrent) = 0;

    [[nodiscard]] ivec2 pos() const { return data_.windowPos; }
    [[nodiscard]] ivec2 dims() const { return data_.windowDims; }
    [[nodiscard]] bool isVSync() const { return data_.vSync; }
    [[nodiscard]] bool isFullscreen() const { return data_.fullScreen; }
    [[nodiscard]] bool isUsingCustomDecor() const { return data_.customDecor; }
    void setEventCallback(const EventCallbackFn& callback) { data_.eventCallback = callback; }
    
    static Unique<Window> create(const WindowProperties& props = {});
  protected:
    Window(const WindowProperties& props)
      : data_{props} {
      Renderer::setApi(props.renderApi);
    }

    struct WindowState {
      std::string title;
      ivec2 windowPos, posBeforeFullscreen, windowDims, dimsBeforeFullscreen;
      ivec2 cursorPos{}, cursorPosOld{};
      vec2 cursorDelta{};
      bool vSync;
      bool fullScreen;
      bool borderless;
      bool customDecor;
      EventCallbackFn eventCallback;

      explicit WindowState(const WindowProperties& props)
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