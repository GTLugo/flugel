//
// Created by Gabriel Lugo on 3/29/2021.
//
#include "time.hpp"

#include <GLFW/glfw3.h>

namespace Flugel {
  void Time::initialize() {
    FLUGEL_INFO_E("Initialized time!");
    gameCurrent_ = TimePoint<Seconds>{Seconds{glfwGetTime()}};
  }

  void Time::tick() {
    // FLUGEL_ENGINE_TRACE("Tick!");
    gameCurrent_ = TimePoint<Seconds>{Seconds{glfwGetTime()}};
    delta_ = TimePoint<Seconds>{gameCurrent_ - gameLast_};
    gameLast_ = gameCurrent_;
  }
}