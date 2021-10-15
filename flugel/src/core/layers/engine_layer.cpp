#include "engine_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

#include <glad/glad.h>

namespace fge {
  void EngineLayer::onRenderEvent(AppRenderEvent& e) {
    glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
    glClear(GL_COLOR_BUFFER_BIT);
    
    App::instance().window().context().swapBuffers();
  }

  bool EngineLayer::onWindowEvent(WindowEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case WindowEventType::Close: {
        FGE_DEBUG_ENG("{0}: {1}", name_, e);
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
      FGE_DEBUG_ENG("{0}: Fullscreen({1})", name_, !App::instance().window().isFullscreen());
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
      if (e.buttonState() == Mouse::Pressed
        && Input::cursorPos().y < 50 && Input::cursorPos().x < (App::instance().window().dims().x - 50)) {
        draggingWindowDecor_ = true;
        windowDragOffset_ = {glm::floor(Input::cursorPos().x), glm::floor(Input::cursorPos().y)};
      } else {
        draggingWindowDecor_ = false;
      }
      if (closingWindowDecor_ && e.buttonState() == Mouse::Released
        && Input::cursorPos().y < 50 && Input::cursorPos().x >= (App::instance().window().dims().x - 50)) {
        App::instance().close();
      }
      if (e.buttonState() == Mouse::Pressed
        && Input::cursorPos().y < 50 && Input::cursorPos().x >= (App::instance().window().dims().x - 50)) {
        closingWindowDecor_ = true;
      } else {
        closingWindowDecor_ = false;
      }
    }
  }
}