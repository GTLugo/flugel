#pragma once

#include "core/thread_pool/thread_pool.hpp"
#include "core/window/window.hpp"
#include "core/layers/layer_stack.hpp"
#include "core/layers/engine_layer.hpp"
#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

namespace fge {
  class FGE_API App {
  public:
    App(const WindowProperties& props = {});
    virtual ~App();

    static App& instance() { return *instance_; }
    static const Time& time() { return instance_->time_; }
    Window& window() { return *window_; }

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    void run();
    void close();
  private:
    static App* instance_;
    // Util
    /// TODO: Handle multithreaded time. (Perhaps one time per thread?)
    Time time_{};
    // Window
    Unique<Window> window_;
    bool shouldClose_{false};
    // Threads
    ThreadPool threadPool_{};
    // Layers
    LayerStack layerStack_;
    EngineLayer* engineLayer_;
    
    void splitThreads();
    void joinThreads();

    void gameLoop();
    void renderLoop();

    void pollEvents();
    
    void eventDispatch(Event& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}