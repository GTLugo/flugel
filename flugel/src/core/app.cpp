#include "app.hpp"

#include "core/input/input.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <boost/range/adaptor/reversed.hpp>

namespace Flugel {
  App* App::instance_ = nullptr;

  App::App(const WindowProperties& props) {
    FLUGEL_DEBUG_E("Current working directory: {0}", std::filesystem::current_path());
    FLUGEL_TRACE_E("Constructing App...");
    instance_ = this;
    window_ = Window::create(props);
    window_->setEventCallback(FLUGEL_BIND_FN(eventDispatch));
    
    int32_t width, height;
    uint8_t* icon = stbi_load("res/flugel/icon.png", &width, &height, 0, 4);
    window_->setIcon(icon, width, height);
    stbi_image_free(icon);

    appLayer_ = new AppLayer{};
    pushLayer(appLayer_);
  }

  App::~App() {
    FLUGEL_TRACE_E("Destructing App...");
    killThreads();
    FLUGEL_TRACE_E("App destruction complete!");
  }

  void App::spawnThreads() {
    FLUGEL_TRACE_E("Spawning threads...");
    renderThread_ = std::thread{FLUGEL_BIND_FN(renderThreadMain)};
    gameThread_ = std::thread{FLUGEL_BIND_FN(gameThreadMain)};
  }

  void App::killThreads() {
    FLUGEL_TRACE_E("Killing threads...");
    gameThread_.join();
    renderThread_.join();
  }

  void App::pushLayer(Layer* layer) {
    layerStack_.pushLayer(layer);
  }

  void App::pushOverlay(Layer* overlay) {
    layerStack_.pushOverlay(overlay);
  }

  void App::run() {
    FLUGEL_TRACE_E("Running app on main thread (ID: {0})", std::this_thread::get_id());
    threadNames_.insert(std::pair{std::this_thread::get_id(), "MAIN"});

    spawnThreads();
    while (!shouldClose_) {
      pollEvents();
    }

    FLUGEL_TRACE_E("Exiting app on main thread");
  }
  
  void App::renderThreadMain() {
    FLUGEL_TRACE_E("Starting render thread (ID: {0})", std::this_thread::get_id());
    threadNames_.insert(std::pair{std::this_thread::get_id(), "RENDER"});
    window_->setContextCurrent(true);
    
    // RENDER LOOP
    while (!shouldClose_) {
      AppRenderEvent renderEvent{};
      eventDispatch(renderEvent);
    }

    FLUGEL_TRACE_E("Ending render thread");
  }
  
  void App::gameThreadMain() {
    FLUGEL_TRACE_E("Starting game thread (ID: {0})", std::this_thread::get_id());
    threadNames_.insert(std::pair{std::this_thread::get_id(), "GAME"});
    
    // GAME LOOP
    while (!shouldClose_) {
      // This loop will only occur once every fixedTimeStep, being skipped for every
      // frame which happens between each timestep. If the deltaTime per frame is too
      // long, then for each frame, this loop will occur more than once in order to
      // "catch up" with the proper pacing of physics.
      // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
      while (time_.shouldDoFixedStep()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        AppUpdateFixedEvent updateFixedEvent{};
        eventDispatch(updateFixedEvent);

        // End inner, fixed loop with lag tick
        time_.tickLag();
      }

      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      AppUpdateEvent updateEvent{};
      eventDispatch(updateEvent);

      // End outer, unfixed loop with regular tick
      time_.tick();
    }

    FLUGEL_TRACE_E("Ending game thread");
  }

  void App::pollEvents() {
    window_->pollEvents();
  }

  void App::close() {
    shouldClose_ = true;
  }
  
  void App::eventDispatch(Event& e) {
    //EventDispatcher dispatcher{e};
    
    // LAYER EVENT FNs
    for (auto& layer : boost::adaptors::reverse(layerStack_)) {
      layer->onEvent(e);
      if (e.wasHandled()) {
        break;
      }
    }
  }
}