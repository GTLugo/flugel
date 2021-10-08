#include "app.hpp"

#include "core/input/input.hpp"

#include <GLFW/glfw3.h>
#include <boost/range/adaptor/reversed.hpp>

namespace Flugel {
  Unique<App> App::instance_ = nullptr;

  App::App(const WindowProperties& props) {
    FLUGEL_TRACE_E("Constructing App...");
    instance_ = Unique<App>{this};
    window_ = Window::create(props);
    window_->setEventCallback(FLUGEL_BIND_FN(eventDispatch));
  }

  App::~App() {
    FLUGEL_TRACE_E("Destructing App...");
    killThreads();
    FLUGEL_TRACE_E("App destruction complete!");
  }

  void App::spawnThreads() {
    renderThread_ = std::thread{FLUGEL_BIND_FN(renderThreadMain)};
    gameThread_ = std::thread{FLUGEL_BIND_FN(gameThreadMain)};
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

  void App::updateFixed() {
    for (Layer* layer : layerStack_) {
      layer->updateFixed();
    }
  }

  void App::update() {
    if (draggingWindow_) {
      window_->dragWindow(windowDragOffset_.x, windowDragOffset_.y);
    }

    for (Layer* layer : layerStack_) {
      layer->update();
    }
  }

  void App::render() {
    for (Layer* layer : layerStack_) {
      layer->render();
    }
    window_->render();
  }

  void App::close() {
    shouldClose_ = true;
  }

  void App::pushLayer(Layer* layer) {
    layerStack_.pushLayer(layer);
  }

  void App::pushOverlay(Layer* overlay) {
    layerStack_.pushOverlay(overlay);
  }
  
  void App::eventDispatch(Event& e) {
    EventDispatcher dispatcher{e};

    // PRIMARY EVENT FNs
    dispatcher.tryDispatch<AppEvent>(FLUGEL_BIND_FN(onAppEvent));
    dispatcher.tryDispatch<WindowEvent>(FLUGEL_BIND_FN(onWindowEvent));

    // INPUT EVENT FNs
    dispatcher.tryDispatch<KeyboardEvent>(FLUGEL_BIND_FN(onKeyboardEvent));
    dispatcher.tryDispatch<MouseEvent>(FLUGEL_BIND_FN(onMouseEvent));
    dispatcher.tryDispatch<CursorEvent>(FLUGEL_BIND_FN(onCursorEvent));
    dispatcher.tryDispatch<ScrollEvent>(FLUGEL_BIND_FN(onScrollEvent));
    
    // LAYER EVENT FNs
    for (auto& layer : boost::adaptors::reverse(layerStack_)) {
      layer->onEvent(e);
      if (e.wasHandled()) {
        break;
      }
    }
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
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (Input::isKeyPressed(GLFW_KEY_ENTER) && (e.mods() & GLFW_MOD_ALT)) {
      FLUGEL_DEBUG_E("Fullscreen: {0} [Thread: {1}]", !window_->isFullscreen(), threadNames_.at(std::this_thread::get_id()));
      window_->setFullscreen(!window_->isFullscreen());
    }
    return false; // return false so event isn't marked handled from base app
  }

  bool App::onMouseEvent(MouseEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    // dragging and close button
    if (e.button() == GLFW_MOUSE_BUTTON_LEFT) {
      if (e.buttonState() == ButtonState::Pressed
        && Input::cursorPosY() < 50 && Input::cursorPosX() < (window_->width() - 50)) {
        draggingWindow_ = true;
        windowDragOffset_ = {glm::floor(Input::cursorPosX()), glm::floor(Input::cursorPosY())};
      } else {
        draggingWindow_ = false;
      }
      if (customCloseButton_ && e.buttonState() == ButtonState::Released
        && Input::cursorPosY() < 50 && Input::cursorPosX() >= (window_->width() - 50)) {
        shouldClose_ = true;
      }
      if (e.buttonState() == ButtonState::Pressed
        && Input::cursorPosY() < 50 && Input::cursorPosX() >= (window_->width() - 50)) {
        customCloseButton_ = true;
      } else {
        customCloseButton_ = false;
      }
    }
    return false; // return false so event isn't marked handled from base app
  }

  bool App::onCursorEvent(CursorEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }

  bool App::onScrollEvent(ScrollEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }
}