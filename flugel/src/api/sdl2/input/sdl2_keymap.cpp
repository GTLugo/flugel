#if defined(FLUGEL_USE_SDL2) // API GUARD

#include "core/input/key_codes.hpp"

#include <SDL2/SDL.h>

namespace fge {
  std::map<Key::Code, int32_t> Key::keyMap_{
    {Key::Unknown,      SDL_SCANCODE_UNKNOWN},
    //num row
    {Key::_1,           SDL_SCANCODE_1}, 
    {Key::_2,           SDL_SCANCODE_2}, 
    {Key::_3,           SDL_SCANCODE_3}, 
    {Key::_4,           SDL_SCANCODE_4}, 
    {Key::_5,           SDL_SCANCODE_5},
    {Key::_6,           SDL_SCANCODE_6},
    {Key::_7,           SDL_SCANCODE_7},
    {Key::_8,           SDL_SCANCODE_8},
    {Key::_9,           SDL_SCANCODE_9},
    {Key::_0,           SDL_SCANCODE_0}, 
    // numpad numbers
    {Key::Num1,         SDL_SCANCODE_KP_1},
    {Key::Num2,         SDL_SCANCODE_KP_2},
    {Key::Num3,         SDL_SCANCODE_KP_3},
    {Key::Num4,         SDL_SCANCODE_KP_4},
    {Key::Num5,         SDL_SCANCODE_KP_5},
    {Key::Num6,         SDL_SCANCODE_KP_6},
    {Key::Num7,         SDL_SCANCODE_KP_7},
    {Key::Num8,         SDL_SCANCODE_KP_8},
    {Key::Num9,         SDL_SCANCODE_KP_9},
    {Key::Num0,         SDL_SCANCODE_KP_0}, 
    // f-row part 1
    {Key::F1,           SDL_SCANCODE_F1},
    {Key::F2,           SDL_SCANCODE_F2},
    {Key::F3,           SDL_SCANCODE_F3},
    {Key::F4,           SDL_SCANCODE_F4},
    {Key::F5,           SDL_SCANCODE_F5},
    {Key::F6,           SDL_SCANCODE_F6},
    {Key::F7,           SDL_SCANCODE_F7},
    {Key::F8,           SDL_SCANCODE_F8},
    {Key::F9,           SDL_SCANCODE_F9},
    {Key::F10,          SDL_SCANCODE_F10}, 
    // f-row electric boogaloo
    {Key::F11,          SDL_SCANCODE_F11},
    {Key::F12,          SDL_SCANCODE_F12},
    {Key::F13,          SDL_SCANCODE_F13},
    {Key::F14,          SDL_SCANCODE_F14},
    {Key::F15,          SDL_SCANCODE_F15},
    {Key::F16,          SDL_SCANCODE_F16},
    {Key::F17,          SDL_SCANCODE_F17},
    {Key::F18,          SDL_SCANCODE_F18},
    {Key::F19,          SDL_SCANCODE_F19},
    {Key::F20,          SDL_SCANCODE_F20}, 
    // f-row part 3
    {Key::F21,          SDL_SCANCODE_F21},
    {Key::F22,          SDL_SCANCODE_F22},
    {Key::F23,          SDL_SCANCODE_F23},
    {Key::F24,          SDL_SCANCODE_F24},
    {Key::F25,          SDL_SCANCODE_UNKNOWN},
    // letters
    {Key::A,            SDL_SCANCODE_A},
    {Key::B,            SDL_SCANCODE_B},
    {Key::C,            SDL_SCANCODE_C},
    {Key::D,            SDL_SCANCODE_D},
    {Key::E,            SDL_SCANCODE_E},
    {Key::F,            SDL_SCANCODE_F},
    {Key::G,            SDL_SCANCODE_G},
    {Key::H,            SDL_SCANCODE_H},
    {Key::I,            SDL_SCANCODE_I},
    {Key::J,            SDL_SCANCODE_J},
    {Key::K,            SDL_SCANCODE_K},
    {Key::L,            SDL_SCANCODE_L},
    {Key::M,            SDL_SCANCODE_M},
    {Key::N,            SDL_SCANCODE_N},
    {Key::O,            SDL_SCANCODE_O},
    {Key::P,            SDL_SCANCODE_P},
    {Key::Q,            SDL_SCANCODE_Q},
    {Key::R,            SDL_SCANCODE_R},
    {Key::S,            SDL_SCANCODE_S},
    {Key::T,            SDL_SCANCODE_T},
    {Key::U,            SDL_SCANCODE_U},
    {Key::V,            SDL_SCANCODE_V},
    {Key::W,            SDL_SCANCODE_W},
    {Key::X,            SDL_SCANCODE_X},
    {Key::Y,            SDL_SCANCODE_Y},
    {Key::Z,            SDL_SCANCODE_Z},
    // whitespace
    {Key::Space,        SDL_SCANCODE_SPACE},
    {Key::Tab,          SDL_SCANCODE_TAB},
    {Key::Enter,        SDL_SCANCODE_RETURN},
    {Key::NumEnter,     SDL_SCANCODE_KP_ENTER},
    // punctuation
    {Key::Semicolon,    SDL_SCANCODE_SEMICOLON},
    {Key::Period,       SDL_SCANCODE_PERIOD},
    {Key::Comma,        SDL_SCANCODE_COMMA},
    {Key::Apostrophe,   SDL_SCANCODE_APOSTROPHE},
    {Key::Accent,       SDL_SCANCODE_GRAVE},
    // math
    {Key::Minus,        SDL_SCANCODE_MINUS},
    {Key::Equal,        SDL_SCANCODE_EQUALS},
    {Key::ForwardSlash, SDL_SCANCODE_SLASH},
    {Key::BackSlash,    SDL_SCANCODE_BACKSLASH},
    // brackets
    {Key::LeftBracket,  SDL_SCANCODE_LEFTBRACKET},
    {Key::RightBracket, SDL_SCANCODE_RIGHTBRACKET},
    // non-visible
    {Key::Escape,       SDL_SCANCODE_ESCAPE},
    {Key::Menu,         SDL_SCANCODE_MENU},
    {Key::Pause,        SDL_SCANCODE_PAUSE},
    {Key::Backspace,    SDL_SCANCODE_BACKSPACE},
    {Key::Insert,       SDL_SCANCODE_INSERT},
    {Key::Delete,       SDL_SCANCODE_DELETE},
    {Key::PrintScreen,  SDL_SCANCODE_PRINTSCREEN},
    // locks
    {Key::CapsLock,     SDL_SCANCODE_CAPSLOCK},
    {Key::ScrollLock,   SDL_SCANCODE_SCROLLLOCK},
    {Key::NumLock,      SDL_SCANCODE_NUMLOCKCLEAR},
    // direction
    {Key::Up,           SDL_SCANCODE_UP},
    {Key::Down,         SDL_SCANCODE_DOWN},
    {Key::Left,         SDL_SCANCODE_LEFT},
    {Key::Right,        SDL_SCANCODE_RIGHT},
    {Key::PageUp,       SDL_SCANCODE_PAGEUP},
    {Key::PageDown,     SDL_SCANCODE_PAGEDOWN},
    {Key::Home,         SDL_SCANCODE_HOME},
    {Key::End,          SDL_SCANCODE_END},
    // numpad math
    {Key::NumPeriod,    SDL_SCANCODE_KP_DECIMAL},
    {Key::NumPlus,      SDL_SCANCODE_KP_PLUS},
    {Key::NumHyphen,    SDL_SCANCODE_KP_MINUS},
    {Key::NumSlash,     SDL_SCANCODE_KP_DIVIDE},
    {Key::NumAsterisk,  SDL_SCANCODE_KP_MULTIPLY},
    {Key::NumEqual,     SDL_SCANCODE_KP_EQUALS},
    // left modifiers
    {Key::LeftShift,    SDL_SCANCODE_LSHIFT},
    {Key::LeftControl,  SDL_SCANCODE_LCTRL},
    {Key::LeftAlt,      SDL_SCANCODE_LALT},
    {Key::LeftSuper,    SDL_SCANCODE_UNKNOWN},
    // right modifiers
    {Key::RightShift,   SDL_SCANCODE_RSHIFT},
    {Key::RightControl, SDL_SCANCODE_RCTRL},
    {Key::RightAlt,     SDL_SCANCODE_RALT},
    {Key::RightSuper,   SDL_SCANCODE_UNKNOWN},
    // international
    {Key::World1,       SDL_SCANCODE_UNKNOWN},
    {Key::World2,       SDL_SCANCODE_UNKNOWN},
  };

  std::map<Modifier::Code, int32_t> Modifier::modMap_{
    {Modifier::None,     0},
    {Modifier::Shift,    1},
    {Modifier::Control,  2}, 
    {Modifier::Alt,      3}, 
    {Modifier::Super,    4},
    {Modifier::CapsLock, 5},
    {Modifier::NumLock,  6},
  };
}

#endif // API GUARD