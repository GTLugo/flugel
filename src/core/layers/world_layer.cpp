//
// Created by galex on 4/2/2022.
//

#include "world_layer.hpp"

#include "core/app.hpp"

namespace ff {
  bool WorldLayer::onMainEvent(const MainEvent& e) {
    return App::instance().activeWorld().onMainEvent(e);
  }

  bool WorldLayer::onGameEvent(const GameEvent& e) {
    auto& world{App::instance().activeWorld()};
    return world.onGameEvent(e) || world.World::onGameEvent(e);
  }

  bool WorldLayer::onWindowEvent(const WindowEvent& e) {
    return App::instance().activeWorld().onWindowEvent(e);
  }

  bool WorldLayer::onInputEvent(const InputEvent& e) {
    return App::instance().activeWorld().onInputEvent(e);
  }
}