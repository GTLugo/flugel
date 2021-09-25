#pragma once

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

  // abstract
  class FLUGEL_API Window {
  public:
    using EventCallbackFn = std::function<void(Event&)>;
    
    struct WindowData {
      std::string title;
      uint32_t width, height;
      int xPos, yPos;
      bool vsync;
      EventCallbackFn eventCallback;
    };
  public:
    virtual ~Window() {}

    virtual void update() = 0;

    uint32_t getWidth() const { return data_.width; }
    uint32_t getHeight() const { return data_.height; }
    int getX() const { return data_.xPos; }
    int getY() const { return data_.yPos; }
    bool isVsync() const { return data_.vsync; }

    // Window attributes
    void setEventCallback(const EventCallbackFn& callback) { data_.eventCallback = callback; }
    virtual void setVsync(bool enabled) = 0;

    static Unique<Window> create(const WindowProps& props = WindowProps{});
  protected:
    WindowData data_;
  };
}