#include "engine_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

namespace fge {
  void EngineLayer::render() {
    App::instance().window().render();
  }

  bool EngineLayer::onWindowEvent(WindowEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case WindowEventType::Close: {
        FGE_DEBUG_ENG("{0}: {1} [Thread: {2}]", name_, e, App::instance().threadName(std::this_thread::get_id()));
        App::instance().close();
        return true;
      }
      default: {
        return false;
      }
    }
  }

  bool EngineLayer::onKeyboardEvent(KeyboardEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (Input::isPressed(Key::Enter) && Input::isPressed(Key::LeftAlt)) {
      FGE_DEBUG_ENG("{0}: Fullscreen({1}) [Thread: {2}]", name_, !App::instance().window().isFullscreen(), App::instance().threadName(std::this_thread::get_id()));
      App::instance().window().setFullscreen(!App::instance().window().isFullscreen());
    }
    return true;
  }

  bool EngineLayer::onMouseEvent(MouseEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    // custom dragging and close button
    if (App::instance().window().isUsingCustomDecor()) {
      pollCustomDecor(e);
    }
    return true;
  }

  bool EngineLayer::onCursorEvent(CursorEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (draggingWindowDecor_) {
      App::instance().window().dragWindow(windowDragOffset_);
    }
    
    return true;
  }

  bool EngineLayer::onScrollEvent(ScrollEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }
  void EngineLayer::pollCustomDecor(MouseEvent& e) {
    if (App::instance().window().isFullscreen()) {
      draggingWindowDecor_ = false;
      closingWindowDecor_ = false;
      return;
    }
    if (e.button() == Mouse::Left) {
      if (e.buttonState() == ButtonState::Pressed
        && Input::cursorPosY() < 50 && Input::cursorPosX() < (App::instance().window().dims().x - 50)) {
        draggingWindowDecor_ = true;
        windowDragOffset_ = {glm::floor(Input::cursorPosX()), glm::floor(Input::cursorPosY())};
      } else {
        draggingWindowDecor_ = false;
      }
      if (closingWindowDecor_ && e.buttonState() == ButtonState::Released
        && Input::cursorPosY() < 50 && Input::cursorPosX() >= (App::instance().window().dims().x - 50)) {
        App::instance().close();
      }
      if (e.buttonState() == ButtonState::Pressed
        && Input::cursorPosY() < 50 && Input::cursorPosX() >= (App::instance().window().dims().x - 50)) {
        closingWindowDecor_ = true;
      } else {
        closingWindowDecor_ = false;
      }
    }
  }
}