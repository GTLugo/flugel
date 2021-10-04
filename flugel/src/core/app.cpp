#include "app.hpp"

namespace Flugel {
  App::App() {
    FLUGEL_TRACE("Constructing App...");
    appUpdateFixedId_ = updateFixedNotifier.subscribe(FLUGEL_BIND_FN(App::onAppUpdateFixed));
    appUpdateId_ = updateNotifier.subscribe(FLUGEL_BIND_FN(App::onAppUpdate));
    appRenderId_ = renderNotifier.subscribe(FLUGEL_BIND_FN(App::onAppRender));

    windowCloseId_ = window_.closeNotifier.subscribe(FLUGEL_BIND_FN(App::onWindowClose));
  }

  App::~App() {
    FLUGEL_TRACE("Destructing App...");
    updateFixedNotifier.unsubscribe(appUpdateFixedId_);
    updateNotifier.unsubscribe(appUpdateId_);
    renderNotifier.unsubscribe(appRenderId_);

    window_.closeNotifier.unsubscribe(windowCloseId_);
  }

  void App::run() {
    FLUGEL_TRACE("Running...");

    while (!shouldClose_) {
      // Start outer, unfixed loop with regular tick
      time_.tick();
      processInput();

      // This loop will only occur once every fixedTimeStep, being skipped for every
      // frame which happens between each timestep. If the deltaTime per frame is too
      // long, then for each frame, this loop will occur more than once in order to
      // "catch up" with the proper pacing of physics.
      // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
      while (time_.shouldDoFixedStep()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        AppUpdateFixedEvent updateFixedEvent{};
        updateFixedNotifier.notify(updateFixedEvent);

        // End inner, fixed loop with lag tick
        time_.tickLag();
      }

      // Rendering & timestep INSENSITIVE stuff happens out here,
      // where pacing goes as fast as possible
      AppUpdateEvent updateEvent{};
      updateNotifier.notify(updateEvent);

      AppRenderEvent renderEvent{};
      renderNotifier.notify(renderEvent);
    }

    FLUGEL_TRACE("Finished running!");
  }

  void App::processInput() {
    //FLUGEL_TRACE("FPS: {0}", 1. / time_.deltaTime<Seconds>());
    window_.processInput();
  }

  bool App::onAppUpdateFixed(AppUpdateFixedEvent& e) {
    FLUGEL_TRACE("FixedUpdate!");
    return false;
  }

  bool App::onAppUpdate(AppUpdateEvent& e) {
    //FLUGEL_TRACE("Update!");
    return false;
  }

  bool App::onAppRender(AppRenderEvent& e) {
    //FLUGEL_TRACE("Render!");
    //glViewport(0, 0, window_.width, window_.height);
    //glClearColor(1.f, 0.f, 1.f, 1.f);
    //glClear(GL_COLOR_BUFFER_BIT);

    window_.swapBuffer();

    return false;
  }

  bool App::onAppTick(AppTickEvent& e) {
    //FLUGEL_TRACE("Tick!");
    return false;
  }
  
  bool App::onWindowClose(WindowCloseEvent& e) {
    shouldClose_ = true;
    return false;
  }
}