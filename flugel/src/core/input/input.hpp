#pragma once

#include "key_codes.hpp"
#include "mouse_codes.hpp"

namespace fge {
  class FGE_API Input {
  public:
    static bool isPressed(Key::Code key);
    static bool isPressed(Mouse::Code button);
    //static bool isPressed(Modifier::Codes mods);
    static vector2_t cursorPos();
    static double cursorPosX();
    static double cursorPosY();
  };
}