//
// Created by galex on 4/2/2022.
//

#include "world_layer.hpp"

#include "core/app.hpp"

namespace ff {
  bool WorldLayer::onWindowEvent(const WindowEvent& e) {
    return App::instance().activeWorld()->onWindowEvent(e);
  }

  bool WorldLayer::onAppEvent(const AppEvent& e) {
    return App::instance().activeWorld()->onAppEvent(e);
  }

  bool WorldLayer::onLogicEvent(const LogicEvent& e) {
    auto world{App::instance().activeWorld()};
    return world->World::onLogicEvent(e) || world->onLogicEvent(e);
  }

  bool WorldLayer::onRenderEvent(const RenderEvent& e) {
    return App::instance().activeWorld()->onRenderEvent(e);
  }

  bool WorldLayer::onKeyboardEvent(const KeyboardEvent& e) {
    return App::instance().activeWorld()->onKeyboardEvent(e);
  }

  bool WorldLayer::onMouseEvent(const MouseEvent& e) {
    return App::instance().activeWorld()->onMouseEvent(e);
  }

  bool WorldLayer::onCursorEvent(const CursorEvent& e) {
    return App::instance().activeWorld()->onCursorEvent(e);
  }

  bool WorldLayer::onScrollEvent(const ScrollEvent& e) {
    return App::instance().activeWorld()->onScrollEvent(e);
  }
}