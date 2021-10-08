#pragma once

#include "core/window/window.hpp"
#include "core/layers/layer_stack.hpp"
#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

namespace Flugel {
  class FLUGEL_API App {
  public:
    App(const WindowProperties& props = {});
    virtual ~App();

    static App& instance() { return *instance_; }
    const Time& time() const { return time_; }
    Window& window() { return *window_; }

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    void run();
  private:
    static Unique<App> instance_;
    // Util
    Time time_{};
    // Window
    Unique<Window> window_;
    bool shouldClose_{false};
    bool draggingWindow_{false};
    bool closingWindow_{false};
    glm::vec2 windowDragOffset_; // cursor position at time of clicking to drag window
    // Threads
    std::thread gameThread_;
    std::thread renderThread_;
    std::map<std::thread::id, std::string> threadNames_{};
    // Layers
    LayerStack layerStack_;
    
    void spawnThreads();
    void killThreads();

    void gameThreadMain();
    void renderThreadMain();

    void pollEvents();
    void updateFixed();
    void update();
    void render();
    void close();
    
    void eventDispatch(Event& e);
    bool onAppEvent(AppEvent& e);
    bool onWindowEvent(WindowEvent& e);
    bool onKeyboardEvent(KeyboardEvent& e);
    bool onMouseEvent(MouseEvent& e);
    bool onCursorEvent(CursorEvent& e);
    bool onScrollEvent(ScrollEvent& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}