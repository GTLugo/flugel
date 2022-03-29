#pragma once

#include "core/window/window.hpp"
#include "core/layers/layer_stack.hpp"
#include "core/layers/engine_layer.hpp"

#include "core/callbacks/event_system.hpp"
#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/notifier/notifier.hpp"

#include "core/threading/job_system.hpp"

namespace ff {
  class App {
  public:
    explicit App(const WindowProperties& props = {});
    virtual ~App();

    static App& instance() { return *instance_; }
    Window& window() { return *window_; }

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    void run();
    void close();

    App(const App& app) = delete;
    App& operator=(const App& app) = delete;
  private:
    static inline App* instance_{nullptr};

    // Util
    float tickRate_{128.f};

    // Window
    Unique<Window> window_;
    bool shouldClose_{false};
    vec2 windowDragOffset_{}; // cursor position at time of clicking to drag window
    bool draggingWindowDecor_{false};
    bool closingWindowDecor_{false};
    Color clearColor_{0x00FF00FF}; // 0x2D2A2AFF
    Shared<FrameBuffer> defaultFrameBuffer_;

    // Layers
    LayerStack layerStack_;

    void gameLoop();

    void eventHandler(const Event& e);

    struct TimeJobArgs {
      float tickRate{128.f};
    };

    struct EventSystemJobArgs {
      EventSystem::EventCallbackFn callbackFn;
    };
  };

  Unique<App> createApp();
}