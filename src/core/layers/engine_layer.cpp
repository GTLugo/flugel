#include "engine_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

namespace ff {
  bool EngineLayer::onMainEvent(const MainEvent& e) {
    return std::visit(EventVisitor{
      [](const MainPollEvent&) {
        App::instance().window().pollEvents();
        return true;
      },
      [](const auto& event) { return false; }
    }, e);
  }

  bool EngineLayer::onGameEvent(const GameEvent& e) {
    return std::visit(EventVisitor{
        [=](const GameStartEvent&) {
          App& app{App::instance()};
          defaultFrameBuffer_ = FrameBuffer::create(
              TextureBuffer::Format::RGB,
              App::instance().window().dims().x,
              App::instance().window().dims().y,
              nullptr);
          Renderer::setDefaultFrameBuffer(defaultFrameBuffer_);

          return true;
        },
        [=](const GameBeginFrameEvent&) {
          Renderer::clear(clearColor_);
          Renderer::beginScene();

          return true;
        },
        [=](const GameEndFrameEvent&) {
          Renderer::endScene();
          //Renderer::flush();
          App::instance().window().context().swapBuffers();

          return true;
        },
        [](const auto& event) { return false; }
    }, e);
  }

  bool EngineLayer::onWindowEvent(const WindowEvent& e) {
    return std::visit(EventVisitor{
        [=](const WindowCloseEvent& keyEvent) {
          Log::debug_e("{0}: {1}", name_, keyEvent);
          App::instance().close();
          return true;
        },
        [=](const auto& keyEvent) { return false; },
    }, e);
  }

  bool EngineLayer::onInputEvent(const InputEvent& e) {
    return std::visit(EventVisitor{
      [=](const InputKeyEvent& keyEvent) {
        if (Input::isPressed(Key::Enter) && Input::isPressed(Modifier::Alt)) {
          Log::debug_e("{0}: Fullscreen({1})", name_, !App::instance().window().isFullscreen());
          App::instance().window().setFullscreen(!App::instance().window().isFullscreen());
        }
        return true;
      },
      [=](const InputMouseEvent& mouseEvent) {
        // custom dragging and close button
        if (App::instance().window().isUsingCustomDecor()) {
          pollCustomDecor(mouseEvent);
        }
        return true;
      },
      [=](const InputCursorEvent& cursorEvent) {
        if (draggingWindowDecor_) {
          App::instance().window().dragWindow(windowDragOffset_);
        }
        return true;
      },
      [](const auto& keyEvent) { return false; },
    }, e);
  }

  void EngineLayer::pollCustomDecor(const InputMouseEvent& e) {
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