#if defined(FLUGEL_USE_SDL2) // API GUARD

#include "core/input/input.hpp"

#include "core/app.hpp"

#include <SDL2/SDL.h>

namespace fge {
  bool Input::isPressed(Key::Code key) {
    auto state = SDL_GetKeyboardState(nullptr);
    return state[Key::toNative(key)] == SDL_PRESSED;
  }

  bool Input::isPressed(Mouse::Code button) {
    ivec2 pos;
    auto state = SDL_GetMouseState(&pos.x, &pos.y);
    return state & SDL_BUTTON(Mouse::toNative(button)) != 0;
  }

  dvec2 Input::cursorPos() {
    ivec2 pos;
    auto state = SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
  }
}

#endif // API GUARD