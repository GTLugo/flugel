#include "app.hpp"

#include "events/window_event.hpp"
#include "events/app_event.hpp"

namespace Flugel {
  App::App(const WindowProps& props) {
    window_ = Window::create(props);
    time_.initialize();

    window_->setEventCallback(FLUGEL_BIND_EVENT(App::onEvent));
  }

  App::~App() {
    
  }

  void App::run() {
    FLUGEL_INFO("Running...");

    while (!shouldClose_) {
      time_.tick();
      
      window_->update();
    }
    
    FLUGEL_INFO("Finished running!");
  }

  void App::onEvent(Event& e) {
    #if defined(FLUGEL_LOG_ALL_EVENTS)
      FLUGEL_TRACE_E("{0}", e);
    #endif
    
    EventDispatcher dispatcher{e};
    dispatcher.dispatch<WindowCloseEvent>(FLUGEL_BIND_EVENT(onWindowClosed));

    dispatcher.dispatch<AppStartEvent>(FLUGEL_BIND_EVENT(onStart));
    dispatcher.dispatch<AppTickEvent>(FLUGEL_BIND_EVENT(onTick));
    dispatcher.dispatch<AppUpdateEvent>(FLUGEL_BIND_EVENT(onUpdate));
    dispatcher.dispatch<AppRenderEvent>(FLUGEL_BIND_EVENT(onRender));
  }

  bool App::onStart(AppStartEvent& e) {
    // fps_stopwatch_.start();
    return true;
  }

  bool App::onTick(AppTickEvent& e) {
    time_.tick();
    
    // FLUGEL_ASSERT_ENGINE(fps_stopwatch_.getTimeElapsed<Seconds>() >= 0, "Time went negative?!");
    // if (fps_stopwatch_.getTimeElapsed<Seconds>() >= 1) {
    //   FLUGEL_DEBUG("FPS ({0})", 1.0 / time_.deltaTime<Seconds>());
    //   fps_stopwatch_.start();
    // }
    return true;
  }

  bool App::onUpdate(AppUpdateEvent& e) {
    window_->update();
    return true;
  }

  bool App::onRender(AppRenderEvent& e) {
    
    return true;
  }
  
  bool App::onWindowClosed(WindowCloseEvent& e) {

    return true;
  }
}