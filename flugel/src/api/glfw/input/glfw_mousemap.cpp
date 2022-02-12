
#if defined(FLUGEL_USE_GLFW) // API GUARD

#include "core/input/mouse_codes.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  std::map<Mouse::Code, int32_t> Mouse::mouseMap_{
    {Mouse::Unknown, -1},
    {Mouse::_1,      GLFW_MOUSE_BUTTON_1}, 
    {Mouse::_2,      GLFW_MOUSE_BUTTON_2}, 
    {Mouse::_3,      GLFW_MOUSE_BUTTON_3}, 
    {Mouse::_4,      GLFW_MOUSE_BUTTON_4}, 
    {Mouse::_5,      GLFW_MOUSE_BUTTON_5},
    {Mouse::_6,      GLFW_MOUSE_BUTTON_6},
    {Mouse::_7,      GLFW_MOUSE_BUTTON_7},
    {Mouse::_8,      GLFW_MOUSE_BUTTON_8},
    
    {Mouse::Left,    GLFW_MOUSE_BUTTON_1}, 
    {Mouse::Right,   GLFW_MOUSE_BUTTON_2}, 
    {Mouse::Middle,  GLFW_MOUSE_BUTTON_3}, 
    {Mouse::Back,    GLFW_MOUSE_BUTTON_4}, 
    {Mouse::Forward, GLFW_MOUSE_BUTTON_5},
  };
}

#endif // API GUARD