#if defined(FLUGEL_USE_GLFW) // API GUARD

#include "core/input/key_codes.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  std::map<Key::Code, int32_t> Key::keyMap_{
    {Key::Unknown,      GLFW_KEY_UNKNOWN},
    //num row
    {Key::_1,           GLFW_KEY_1}, 
    {Key::_2,           GLFW_KEY_2}, 
    {Key::_3,           GLFW_KEY_3}, 
    {Key::_4,           GLFW_KEY_4}, 
    {Key::_5,           GLFW_KEY_5},
    {Key::_6,           GLFW_KEY_6},
    {Key::_7,           GLFW_KEY_7},
    {Key::_8,           GLFW_KEY_8},
    {Key::_9,           GLFW_KEY_9},
    {Key::_0,           GLFW_KEY_0}, 
    // numpad numbers
    {Key::Num1,         GLFW_KEY_KP_1},
    {Key::Num2,         GLFW_KEY_KP_2},
    {Key::Num3,         GLFW_KEY_KP_3},
    {Key::Num4,         GLFW_KEY_KP_4},
    {Key::Num5,         GLFW_KEY_KP_5},
    {Key::Num6,         GLFW_KEY_KP_6},
    {Key::Num7,         GLFW_KEY_KP_7},
    {Key::Num8,         GLFW_KEY_KP_8},
    {Key::Num9,         GLFW_KEY_KP_9},
    {Key::Num0,         GLFW_KEY_KP_0}, 
    // f-row part 1
    {Key::F1,           GLFW_KEY_F1},
    {Key::F2,           GLFW_KEY_F2},
    {Key::F3,           GLFW_KEY_F3},
    {Key::F4,           GLFW_KEY_F4},
    {Key::F5,           GLFW_KEY_F5},
    {Key::F6,           GLFW_KEY_F6},
    {Key::F7,           GLFW_KEY_F7},
    {Key::F8,           GLFW_KEY_F8},
    {Key::F9,           GLFW_KEY_F9},
    {Key::F10,          GLFW_KEY_F10}, 
    // f-row electric boogaloo
    {Key::F11,          GLFW_KEY_F11},
    {Key::F12,          GLFW_KEY_F12},
    {Key::F13,          GLFW_KEY_F13},
    {Key::F14,          GLFW_KEY_F14},
    {Key::F15,          GLFW_KEY_F15},
    {Key::F16,          GLFW_KEY_F16},
    {Key::F17,          GLFW_KEY_F17},
    {Key::F18,          GLFW_KEY_F18},
    {Key::F19,          GLFW_KEY_F19},
    {Key::F20,          GLFW_KEY_F20}, 
    // f-row part 3
    {Key::F21,          GLFW_KEY_F21},
    {Key::F22,          GLFW_KEY_F22},
    {Key::F23,          GLFW_KEY_F23},
    {Key::F24,          GLFW_KEY_F24},
    {Key::F25,          GLFW_KEY_F25}, 
    // letters
    {Key::A,            GLFW_KEY_A},
    {Key::B,            GLFW_KEY_B},
    {Key::C,            GLFW_KEY_C},
    {Key::D,            GLFW_KEY_D},
    {Key::E,            GLFW_KEY_E},
    {Key::F,            GLFW_KEY_F},
    {Key::G,            GLFW_KEY_G},
    {Key::H,            GLFW_KEY_H},
    {Key::I,            GLFW_KEY_I},
    {Key::J,            GLFW_KEY_J},
    {Key::K,            GLFW_KEY_K},
    {Key::L,            GLFW_KEY_L},
    {Key::M,            GLFW_KEY_M},
    {Key::N,            GLFW_KEY_N},
    {Key::O,            GLFW_KEY_O},
    {Key::P,            GLFW_KEY_P},
    {Key::Q,            GLFW_KEY_Q},
    {Key::R,            GLFW_KEY_R},
    {Key::S,            GLFW_KEY_S},
    {Key::T,            GLFW_KEY_T},
    {Key::U,            GLFW_KEY_U},
    {Key::V,            GLFW_KEY_V},
    {Key::W,            GLFW_KEY_W},
    {Key::X,            GLFW_KEY_X},
    {Key::Y,            GLFW_KEY_Y},
    {Key::Z,            GLFW_KEY_Z},
    // whitespace
    {Key::Space,        GLFW_KEY_SPACE},
    {Key::Tab,          GLFW_KEY_TAB},
    {Key::Enter,        GLFW_KEY_ENTER},
    {Key::NumEnter,     GLFW_KEY_KP_ENTER},
    // punctuation
    {Key::Semicolon,    GLFW_KEY_SEMICOLON},
    {Key::Period,       GLFW_KEY_PERIOD},
    {Key::Comma,        GLFW_KEY_COMMA},
    {Key::Apostrophe,   GLFW_KEY_APOSTROPHE},
    // math
    {Key::Minus,        GLFW_KEY_MINUS},
    {Key::Equal,        GLFW_KEY_EQUAL},
    {Key::ForwardSlash, GLFW_KEY_SLASH},
    {Key::BackSlash,    GLFW_KEY_BACKSLASH},
    // brackets
    {Key::LeftBracket,  GLFW_KEY_LEFT_BRACKET},
    {Key::RightBracket, GLFW_KEY_RIGHT_BRACKET},
    // non-visible
    {Key::Escape,       GLFW_KEY_ESCAPE},
    {Key::Menu,         GLFW_KEY_MENU},
    {Key::Pause,        GLFW_KEY_PAUSE},
    {Key::Backspace,    GLFW_KEY_BACKSPACE},
    {Key::Insert,       GLFW_KEY_INSERT},
    {Key::Delete,       GLFW_KEY_DELETE},
    {Key::PrintScreen,  GLFW_KEY_PRINT_SCREEN},
    // locks
    {Key::CapsLock,     GLFW_KEY_CAPS_LOCK},
    {Key::ScrollLock,   GLFW_KEY_SCROLL_LOCK},
    {Key::NumLock,      GLFW_KEY_NUM_LOCK},
    // direction
    {Key::Up,           GLFW_KEY_UP},
    {Key::Down,         GLFW_KEY_DOWN},
    {Key::Left,         GLFW_KEY_LEFT},
    {Key::Right,        GLFW_KEY_RIGHT},
    {Key::PageUp,       GLFW_KEY_PAGE_UP},
    {Key::PageDown,     GLFW_KEY_PAGE_DOWN},
    {Key::Home,         GLFW_KEY_HOME},
    {Key::End,          GLFW_KEY_END},
    // numpad math
    {Key::NumPeriod,    GLFW_KEY_KP_DECIMAL},
    {Key::NumPlus,      GLFW_KEY_KP_ADD},
    {Key::NumHyphen,    GLFW_KEY_KP_SUBTRACT},
    {Key::NumSlash,     GLFW_KEY_KP_DIVIDE},
    {Key::NumAsterisk,  GLFW_KEY_KP_MULTIPLY},
    {Key::NumEqual,     GLFW_KEY_KP_EQUAL},
    // left modifiers
    {Key::LeftShift,    GLFW_KEY_LEFT_SHIFT},
    {Key::LeftControl,  GLFW_KEY_LEFT_CONTROL},
    {Key::LeftAlt,      GLFW_KEY_LEFT_ALT},
    {Key::LeftSuper,    GLFW_KEY_LEFT_SUPER},
    // right modifiers
    {Key::RightShift,   GLFW_KEY_RIGHT_SHIFT},
    {Key::RightControl, GLFW_KEY_RIGHT_CONTROL},
    {Key::RightAlt,     GLFW_KEY_RIGHT_ALT},
    {Key::RightSuper,   GLFW_KEY_RIGHT_SUPER},
    // international
    {Key::World1,       GLFW_KEY_WORLD_1},
    {Key::World2,       GLFW_KEY_WORLD_2},
  };

  int32_t Key::toNative(Key::Code key) { 
    return Key::keyMap_.at(key);
  }
  
  Key::Code Key::fromNative(int32_t key) {
    for (const auto& itr : keyMap_) {
      if (itr.second == key) {
        return itr.first;
      }
    } 
    return Key::Unknown;
  };

  std::map<Modifier::Code, int32_t> Modifier::modMap_{
    {Modifier::None,     0}, 
    {Modifier::Shift,    GLFW_MOD_SHIFT},
    {Modifier::Control,  GLFW_MOD_CONTROL}, 
    {Modifier::Alt,      GLFW_MOD_ALT}, 
    {Modifier::Super,    GLFW_MOD_SUPER},
    {Modifier::CapsLock, GLFW_MOD_CAPS_LOCK},
    {Modifier::NumLock,  GLFW_MOD_NUM_LOCK},
  };


  int32_t Modifier::toNative(Modifier::Code mod) { 
    return modMap_.at(mod); 
  }

  int32_t Modifier::toNativeBits(Modifier::BitCodes mods) {
    int32_t result{0};
    if (mods & Shift)    result |= toNative(Shift);
    if (mods & Control)  result |= toNative(Control);
    if (mods & Alt)      result |= toNative(Alt);
    if (mods & Super)    result |= toNative(Super);
    if (mods & CapsLock) result |= toNative(CapsLock);
    if (mods & NumLock)  result |= toNative(NumLock);
    return result;
  }

  Modifier::Code Modifier::fromNative(int32_t mod) {
    int32_t modifiers{0};
    for (const auto& itr : modMap_) {
      if (itr.second == mod) {
        return itr.first;
      }
    }
    return Modifier::None;
  };

  Modifier::BitCodes Modifier::fromNativeBits(int32_t mods) {
    Modifier::BitCodes result{0};
    if (mods & toNative(Shift))    result |= Shift;
    if (mods & toNative(Control))  result |= Control;
    if (mods & toNative(Alt))      result |= Alt;
    if (mods & toNative(Super))    result |= Super;
    if (mods & toNative(CapsLock)) result |= CapsLock;
    if (mods & toNative(NumLock))  result |= NumLock;
    return result;
  }
}

#endif // API GUARD