#pragma once

#include "flugel/events/event.hpp"

namespace Flugel {
  struct WindowProps {
    std::string title;
    uint32_t width, height;
    bool vsync;

    WindowProps(const std::string& title = "Flugel Engine",
                uint32_t width = 800,
                uint32_t height = 450,
                bool vsync = true)
      : title{title}, width{width}, height{height}, vsync{vsync} {}
  };

  class FLUGEL_API Window {
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void onUpdate() = 0;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    // Window attributes
    virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    virtual void setVsync(bool enabled) = 0;
    virtual bool isVsync() const = 0;

    static Window* create(const WindowProps& props = WindowProps{});
  };
}