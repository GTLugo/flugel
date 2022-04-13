#pragma once

#include "key_codes.hpp"
#include "mouse_codes.hpp"

namespace ff {
  class Input {
  public:
    static bool isPressed(Key::Code key);
    static bool isPressed(Mouse::Code button);
    static bool isPressed(Modifier::BitCodes mods);
    static dvec2 cursorPos();
  };
}