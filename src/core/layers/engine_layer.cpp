#include "engine_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

#include <glad/gl.h>

namespace ff {
  bool EngineLayer::onWindowEvent(const WindowEvent& e) {
    //Log::debug_e("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.action()) {
      case WindowEvent::Close: {
        Log::debug_e("{0}: {1}", name_, e);
        App::instance().close();
        return true;
      }
      default: {
        return false;
      }
    }
  }
  
  bool EngineLayer::onAppEvent(const AppEvent& e) {
    switch (e.action()) {
      case AppEvent::Poll: {
        App::instance().window().pollEvents();
        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool EngineLayer::onRenderEvent(const RenderEvent& e) {
    switch (e.action()) {
      case RenderEvent::Start: {
        App& app{App::instance()};
        defaultFrameBuffer_ = FrameBuffer::create(
            TextureBuffer::Format::RGB,
            App::instance().window().dims().x,
            App::instance().window().dims().y,
            nullptr);
        Renderer::setDefaultFrameBuffer(defaultFrameBuffer_);

        return false;
      }
      case RenderEvent::BeginFrame: {
        Renderer::clear(clearColor_);
        Renderer::beginScene();

        return false;
      }
      case RenderEvent::EndFrame: {
        Renderer::endScene();
        //Renderer::flush();
        App::instance().window().context().swapBuffers();

        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool EngineLayer::onKeyboardEvent(const KeyboardEvent& e) {
    //Log::debug_e("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (Input::isPressed(Key::Enter) && Input::isPressed(Modifier::Alt)) {
      Log::debug_e("{0}: Fullscreen({1})", name_, !App::instance().window().isFullscreen());
      App::instance().window().setFullscreen(!App::instance().window().isFullscreen());
    }
    return true;
  }

  bool EngineLayer::onMouseEvent(const MouseEvent& e) {
    // custom dragging and close button
    if (App::instance().window().isUsingCustomDecor()) {
      pollCustomDecor(e);
    }
    return true;
  }

  bool EngineLayer::onCursorEvent(const CursorEvent& e) {
    //Log::debug_e("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (draggingWindowDecor_) {
      App::instance().window().dragWindow(windowDragOffset_);
    }
    return true;
  }

  bool EngineLayer::onScrollEvent(const ScrollEvent& e) {
    //Log::debug_e("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }
  void EngineLayer::pollCustomDecor(const MouseEvent& e) {
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