#pragma once

#include "core/thread_pool/thread_pool.hpp"
#include "core/window/window.hpp"
#include "core/layers/layer_stack.hpp"
#include "core/layers/engine_layer.hpp"
#include "core/layers/render_layer.hpp"

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

namespace fge {
  struct AppState {
    
  };

  class FGE_API App {
  public:
    explicit App(const WindowProperties& props = {});
    virtual ~App();

    static App& instance() { return *instance_; }
    Window& window() { return *window_; }

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    void run();
    void close();
  private:
    static App* instance_;
    // Util
    AppState state_[2]{}; // double buffered app state
    // Window
    Unique<Window> window_;
    bool shouldClose_{false};

    // Threads
    ThreadPool threadPool_{};
    std::mutex renderMutex_;
    std::condition_variable renderCondition_;
    std::queue<RenderEvent*> renderQueue_{};

    // Layers
    LayerStack layerStack_;
    
    void gameLoop();
    void renderLoop();
    
    void waitForRenderJob();
    void pushRenderJob(std::array<RenderEvent*, 4> renderEvents);

    void eventDispatch(Event& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}