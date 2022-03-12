
#if defined(FLUGEL_USE_SDL2) // API GUARD

#include "core/input/mouse_codes.hpp"

#include <SDL2/SDL.h>

namespace fge {
  std::map<Mouse::Code, i32> Mouse::mouseMap_{
    {Mouse::Unknown, -1},
    {Mouse::_1,      SDL_BUTTON_LEFT}, 
    {Mouse::_2,      SDL_BUTTON_RIGHT}, 
    {Mouse::_3,      SDL_BUTTON_MIDDLE}, 
    {Mouse::_4,      SDL_BUTTON_X1}, 
    {Mouse::_5,      SDL_BUTTON_X2},
    {Mouse::_6,      -1},
    {Mouse::_7,      -1},
    {Mouse::_8,      -1},
    
    {Mouse::Left,    SDL_BUTTON_LEFT}, 
    {Mouse::Right,   SDL_BUTTON_RIGHT}, 
    {Mouse::Middle,  SDL_BUTTON_MIDDLE}, 
    {Mouse::Back,    SDL_BUTTON_X1}, 
    {Mouse::Forward, SDL_BUTTON_X2},
  };
}

#endif // API GUARD