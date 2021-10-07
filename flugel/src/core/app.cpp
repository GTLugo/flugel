#include "app.hpp"

namespace Flugel {
  App::App(const WindowProperties& props) 
    : window_{props} {
    FLUGEL_TRACE_E("Constructing App...");

    window_.setEventCallback(FLUGEL_BIND_FN(App::onEvent));
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

    spawnThreads();
    while (!shouldClose_) {
      processInput();
    }

    FLUGEL_TRACE_E("Exiting app on main thread");
  }
  
  void App::renderThreadMain() {
    FLUGEL_TRACE_E("Starting render thread (ID: {0})", std::this_thread::get_id());
    window_.makeContextCurrent();
    
    // RENDER LOOP
    while (!shouldClose_) {
      AppEvent renderEvent{AppEventType::Render};
      onEvent(renderEvent);
    }

    FLUGEL_TRACE_E("Ending render thread");
  }
  
  void App::gameThreadMain() {
    FLUGEL_TRACE_E("Starting game thread (ID: {0})", std::this_thread::get_id());
    
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
        onEvent(updateFixedEvent);

        // End inner, fixed loop with lag tick
        time_.tickLag();
      }

      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      AppEvent updateEvent{AppEventType::Update};
      onEvent(updateEvent);

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
    static int32_t count = 0;
    if (leftMouseHeld) {
      FLUGEL_INFO_E("Yeet {0}", count++);
    } else {
      count = 0;
    }

    window_.swapBuffers();
  }
  
  void App::onEvent(Event& e) {
    switch (e.category()) {
      case EventCategory::App: {
        //FLUGEL_DEBUG_E("{0} [Thread ID: {1}]", e, std::this_thread::get_id());
        auto& appEvent = dynamic_cast<AppEvent&>(e);
        switch (appEvent.type()) {
          case AppEventType::UpdateFixed: {
            updateFixed();
            break;
          }
          case AppEventType::Update: {
            update();
            break;
          }
          case AppEventType::Render: {
            render();
            break;
          }
          default: {
            break;
          }
        }
        break;
      }
      case EventCategory::Window: {
        auto& windowEvent = dynamic_cast<WindowEvent&>(e);
        switch (windowEvent.type()) {
          case WindowEventType::Close: {
            FLUGEL_DEBUG_E("{0} [Thread ID: {1}]", e, std::this_thread::get_id());
            shouldClose_ = true;
            break;
          }
          default: {
            break;
          }
        }
        break;
      }
      case EventCategory::Keyboard: {
        FLUGEL_DEBUG_E("{0} [Thread ID: {1}]", e, std::this_thread::get_id());
        auto& keyboardEvent = dynamic_cast<KeyboardEvent&>(e);

        if (keyboardEvent.keyState() == ButtonState::Pressed 
            && keyboardEvent.key() == GLFW_KEY_ESCAPE) {
          WindowEvent e{WindowEventType::Close, {
            window_.width(), window_.height(),
            window_.xPos(), window_.yPos()
          }};
          onEvent(e);
        }

        break;
      }
      case EventCategory::Mouse: {
        FLUGEL_DEBUG_E("{0} [Thread ID: {1}]", e, std::this_thread::get_id());
        auto& mouseEvent = dynamic_cast<MouseEvent&>(e);

        if (mouseEvent.button() == GLFW_MOUSE_BUTTON_LEFT) {
          leftMouseHeld = mouseEvent.buttonState() == ButtonState::Pressed;
        }
        break;
      }
      case EventCategory::Cursor: {
        //FLUGEL_DEBUG_E("{0} [Thread ID: {1}]", e, std::this_thread::get_id());
        auto& cursorEvent = dynamic_cast<CursorEvent&>(e);

        break;
      }
      case EventCategory::Scroll: {
        //FLUGEL_DEBUG_E("{0} [Thread ID: {1}]", e, std::this_thread::get_id());
        auto& scrollEvent = dynamic_cast<ScrollEvent&>(e);

        break;
      }
      default: {
        break;
      }
    }
  }
}