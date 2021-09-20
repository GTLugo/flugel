#include "app.hpp"

#include "events/app_event.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Flugel {
  App::App(const WindowProps& props) {
    window_ = std::unique_ptr<Window>(Window::create(props));
    time_.initialize();
  }

  App::~App() {
    
  }

  void App::run() {
    FLUGEL_INFO("Running...");

    onStart();
    while (!shouldClose_) {
      onTick();
      onUpdate();
      onRender();
    }
    
    FLUGEL_INFO("Finished running!");
  }

  void App::onStart() {
    fps_stopwatch_.start();
  }

  void App::onTick() {
    time_.tick();
    
    FLUGEL_ASSERT_ENGINE(fps_stopwatch_.getTimeElapsed<Seconds>() >= 0, "Time went negative?!");
    if (fps_stopwatch_.getTimeElapsed<Seconds>() >= 1) {
      FLUGEL_DEBUG("FPS ({0})", 1.0 / time_.deltaTime<Seconds>());
      fps_stopwatch_.start();
    }
  }

  void App::onUpdate() {
    window_->onUpdate();
  }

  void App::onRender() {
    
  }
}