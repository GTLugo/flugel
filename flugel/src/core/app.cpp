#include "app.hpp"

namespace Flugel {
  App::App(const WindowProperties& props) 
    : window_{props} {
    FLUGEL_TRACE_E("Constructing App...");
    // App Events
    appUpdateFixedId_ = updateFixedNotifier_.subscribe(FLUGEL_BIND_FN(App::onAppUpdateFixed));
    appUpdateId_ = updateNotifier_.subscribe(FLUGEL_BIND_FN(App::onAppUpdate));
    appRenderId_ = renderNotifier_.subscribe(FLUGEL_BIND_FN(App::onAppRender));
    // Window Events
    windowCloseId_ = window_.windowCloseNotifier().subscribe(FLUGEL_BIND_FN(App::onWindowClose));
    windowResizeId_ = window_.windowResizeNotifier().subscribe(FLUGEL_BIND_FN(App::onWindowResize));
    windowMovedId_ = window_.windowMovedNotifier().subscribe(FLUGEL_BIND_FN(App::onWindowMoved));
    // Mouse Events
    mousePressedId_ = window_.mousePressedNotifier().subscribe(FLUGEL_BIND_FN(App::onMousePressed));
    mouseReleasedId_ = window_.mouseReleasedNotifier().subscribe(FLUGEL_BIND_FN(App::onMouseReleased));
    mouseMovedId_ = window_.mouseMovedNotifier().subscribe(FLUGEL_BIND_FN(App::onMouseMoved));
    mouseScrolledId_ = window_.mouseScrolledNotifier().subscribe(FLUGEL_BIND_FN(App::onMouseScrolled));
    // Key Events
    keyPressedId_ = window_.keyPressedNotifier().subscribe(FLUGEL_BIND_FN(App::onKeyPressed));
    keyReleasedId_ = window_.keyReleasedNotifier().subscribe(FLUGEL_BIND_FN(App::onKeyReleased));
  }

  App::~App() {
    FLUGEL_TRACE_E("Destructing App...");
    // App Events
    updateFixedNotifier_.unsubscribe(appUpdateFixedId_);
    updateNotifier_.unsubscribe(appUpdateId_);
    renderNotifier_.unsubscribe(appRenderId_);
    // Window Events
    window_.windowCloseNotifier().unsubscribe(windowCloseId_);
    window_.windowResizeNotifier().unsubscribe(windowResizeId_);
    window_.windowMovedNotifier().unsubscribe(windowMovedId_);
    // Mouse Events
    window_.mousePressedNotifier().unsubscribe(mousePressedId_);
    window_.mouseReleasedNotifier().unsubscribe(mouseReleasedId_);
    window_.mouseMovedNotifier().unsubscribe(mouseMovedId_);
    window_.mouseScrolledNotifier().unsubscribe(mouseScrolledId_);
    // Key Events
    window_.keyPressedNotifier().unsubscribe(keyPressedId_);
    window_.keyReleasedNotifier().unsubscribe(keyReleasedId_);
  }

  void App::run() {
    FLUGEL_TRACE_E("Running app...");
    std::thread gamethread{FLUGEL_BIND_FN(App::gameLoop)};
    
    // MAIN THREAD
    while (!shouldClose_) {
      /// TODO: Move input processing off main thread
      processInput();

      AppRenderEvent renderEvent{};
      renderNotifier_.notify(renderEvent);
    }

    gamethread.join();
    FLUGEL_TRACE_E("Exiting app...");
  }
  
  void App::gameLoop() {
    FLUGEL_TRACE_E("Entering game loop...");
    
    // GAME THREAD
    while (!shouldClose_) {
      // Start outer, unfixed loop with regular tick

      // This loop will only occur once every fixedTimeStep, being skipped for every
      // frame which happens between each timestep. If the deltaTime per frame is too
      // long, then for each frame, this loop will occur more than once in order to
      // "catch up" with the proper pacing of physics.
      // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
      while (time_.shouldDoFixedStep()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        AppUpdateFixedEvent updateFixedEvent{};
        updateFixedNotifier_.notify(updateFixedEvent);

        // End inner, fixed loop with lag tick
        time_.tickLag();
      }

      // Rendering & timestep INSENSITIVE stuff happens out here,
      // where pacing goes as fast as possible
      AppUpdateEvent updateEvent{};
      updateNotifier_.notify(updateEvent);

      time_.tick();
    }
    FLUGEL_TRACE_E("Exiting game loop...");
  }

  void App::processInput() {
    //FLUGEL_TRACE_E("FPS: {0}", 1. / time_.deltaTime<Seconds>());
    window_.processInput();
  }

  // App Events

  bool App::onAppUpdateFixed(AppUpdateFixedEvent& e) {
    //FLUGEL_TRACE_E("FixedUpdate!");
    return false;
  }

  bool App::onAppUpdate(AppUpdateEvent& e) {
    //FLUGEL_TRACE_E("Update!");

    return false;
  }

  bool App::onAppRender(AppRenderEvent& e) {
    //FLUGEL_TRACE_E("Render!");
    //glViewport(0, 0, window_.width, window_.height);

    window_.swapBuffers();
    return false;
  }
  
  // Window Events

  bool App::onWindowClose(WindowCloseEvent& e) {
    FLUGEL_TRACE_E("WINDOW_CLOSE");
    shouldClose_ = true;
    return false;
  }
  
  bool App::onWindowResize(WindowResizeEvent& e) {
    //FLUGEL_TRACE_E("WINDOW_RESIZE: ({0}, {1})", e.getWidth(), e.getHeight());
    return false;
  }
  
  bool App::onWindowMoved(WindowMovedEvent& e) {
    //FLUGEL_TRACE_E("WINDOW_MOVED: ({0}, {1})", e.getX(), e.getY());
    return false;
  }

  // Mouse Events

  bool App::onMousePressed(MousePressedEvent& e) {
    FLUGEL_TRACE_E("MOUSE_PRESSED: {0}", e.getMouseButton());
    return false;
  }

  bool App::onMouseReleased(MouseReleasedEvent& e) {
    FLUGEL_TRACE_E("MOUSE_RELEASED: {0}", e.getMouseButton());
    return false;
  }

  bool App::onMouseMoved(MouseMovedEvent& e) {
    //FLUGEL_TRACE_E("MOUSE_MOVED: ({0}, {1})", e.getX(), e.getY());
    return false;
  }

  bool App::onMouseScrolled(MouseScrolledEvent& e) {
    //FLUGEL_TRACE_E("MOUSE_SCROLLED: ({0}, {1})", e.getXOffset(), e.getYOffset());
    return false;
  }

  // Key Events

  bool App::onKeyPressed(KeyPressedEvent& e) {
    FLUGEL_TRACE_E("KEY_PRESSED: ({0}, {1})", e.getKeyCode(), e.getRepeatCount());
    return false;
  }

  bool App::onKeyReleased(KeyReleasedEvent& e) {
    FLUGEL_TRACE_E("KEY_RELEASED: {0}", e.getKeyCode());
    return false;
  }
}