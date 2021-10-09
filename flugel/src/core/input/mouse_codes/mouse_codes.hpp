#pragma once

#if defined(FLUGEL_USE_GLFW)
  #include "glfw_mouse_mappings.hpp"
#endif

namespace fge {
  enum class Mouse {
    //None = 0,
    Left,
    Right,
    Middle,
    Back,
    Forward,
    _6,
    _7,
    _8
  };
}