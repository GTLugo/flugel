#include "app.hpp"

namespace Flugel {
  App::App(const WindowProperties& props) 
    : window_{props} {
    FLUGEL_TRACE_E("Constructing App...");

    window_.setEventCallback(FLUGEL_BIND_FN(App::eventDispatch));
  }

  App::~App() {
    FLUGEL_TRACE_E("Destructing App...");
    killThreads();
    FLUGEL_TRACE_E("App destruction complete!");
  }

  void App::spawnThreads() {
    renderThread_ = std::thread{FLUGEL_BIND_FN(App::renderThreadMain)};
    gameThread_ = std::thread{FLUGEL_BIND_FN(App::gameThreadMain)};
  }

  void App::killThreads() {
    gameThread_.join();
    renderThread_.join();
  }

  void App::run() {
    FLUGEL_TRACE_E("Running app on main thread (ID: {0})", std::this_thread::get_id());
    threadNames_.insert(std::pair{std::this_thread::get_id(), "MAIN"});

    spawnThreads();
    while (!shouldClose_) {
      processInput();
    }

    FLUGEL_TRACE_E("Exiting app on main thread");
  }
  
  void App::renderThreadMain() {
    FLUGEL_TRACE_E("Starting render thread (ID: {0})", std::this_thread::get_id());
    threadNames_.insert(std::pair{std::this_thread::get_id(), "RENDER"});
    window_.makeContextCurrent();
    
    // RENDER LOOP
    while (!shouldClose_) {
      AppEvent renderEvent{AppEventType::Render};
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
        AppEvent updateFixedEvent{AppEventType::UpdateFixed};
        eventDispatch(updateFixedEvent);

        // End inner, fixed loop with lag tick
        time_.tickLag();
      }

      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      AppEvent updateEvent{AppEventType::Update};
      eventDispatch(updateEvent);

      // End outer, unfixed loop with regular tick
      time_.tick();
    }

    FLUGEL_TRACE_E("Ending game thread");
  }

  void App::processInput() {
    window_.processInput();
  }

  void App::updateFixed() {
    
  }

  void App::update() {

  }

  void App::render() {
    window_.swapBuffers();
  }

  void App::close() {
    shouldClose_ = true;
  }
  
  void App::eventDispatch(Event& e) {
    EventDispatcher dispatcher{e};
    if (dispatcher.tryDispatch<AppEvent>(FLUGEL_BIND_FN(App::onAppEvent)))           return;
    if (dispatcher.tryDispatch<WindowEvent>(FLUGEL_BIND_FN(App::onWindowEvent)))     return;
    if (dispatcher.tryDispatch<KeyboardEvent>(FLUGEL_BIND_FN(App::onKeyboardEvent))) return;
    if (dispatcher.tryDispatch<MouseEvent>(FLUGEL_BIND_FN(App::onMouseEvent)))       return;
    if (dispatcher.tryDispatch<CursorEvent>(FLUGEL_BIND_FN(App::onCursorEvent)))     return;
    if (dispatcher.tryDispatch<ScrollEvent>(FLUGEL_BIND_FN(App::onScrollEvent)))     return;
  }

  bool App::onAppEvent(AppEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case AppEventType::UpdateFixed: {
        updateFixed();
        return true;
      }
      case AppEventType::Update: {
        update();
        return true;
      }
      case AppEventType::Render: {
        render();
        return true;
      }
      default: {
        return true;
      }
    }
  }

  bool App::onWindowEvent(WindowEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case WindowEventType::Close: {
        FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
        close();
        return true;
      }
      default: {
        return false;
      }
    }
  }

  bool App::onKeyboardEvent(KeyboardEvent& e) {
    FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }

  bool App::onMouseEvent(MouseEvent& e) {
    FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }

  bool App::onCursorEvent(CursorEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }

  bool App::onScrollEvent(ScrollEvent& e) {
    FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }
}