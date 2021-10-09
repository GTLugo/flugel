#include "app_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

#include "GLFW/glfw3.h"

namespace Flugel {
  void AppLayer::render() {
    App::instance().window().render();
  }

  bool AppLayer::onWindowEvent(WindowEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case WindowEventType::Close: {
        FLUGEL_DEBUG_E("{0}: {1} [Thread: {2}]", name_, e, App::instance().threadName(std::this_thread::get_id()));
        App::instance().close();
        return true;
      }
      default: {
        return false;
      }
    }
  }

  bool AppLayer::onKeyboardEvent(KeyboardEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (Input::isKeyPressed(GLFW_KEY_ENTER) && (e.mods() & GLFW_MOD_ALT)) {
      FLUGEL_DEBUG_E("{0}: Fullscreen({1}) [Thread: {2}]", name_, !App::instance().window().isFullscreen(), App::instance().threadName(std::this_thread::get_id()));
      App::instance().window().setFullscreen(!App::instance().window().isFullscreen());
    }
    return true;
  }

  bool AppLayer::onMouseEvent(MouseEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    // custom dragging and close button
    if (App::instance().window().isUsingCustomDecor()) {
      pollCustomDecor(e);
    }
    return true;
  }

  bool AppLayer::onCursorEvent(CursorEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (draggingWindowDecor_) {
      App::instance().window().dragWindow(windowDragOffset_.x, windowDragOffset_.y);
    }
    
    return true;
  }

  bool AppLayer::onScrollEvent(ScrollEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }
  void AppLayer::pollCustomDecor(MouseEvent& e) {
    if (App::instance().window().isFullscreen()) {
      draggingWindowDecor_ = false;
      closingWindowDecor_ = false;
      return;
    }
    if (e.button() == GLFW_MOUSE_BUTTON_LEFT) {
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