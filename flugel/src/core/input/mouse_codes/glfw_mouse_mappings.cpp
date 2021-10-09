#include "glfw_mouse_mappings.hpp"

#include "GLFW/glfw3.h"

namespace fge {
  std::map<Mouse::Code, int32_t> GlfwMouse::mouseMap_{
    {Mouse::Unknown, -1},
    {Mouse::Left,    GLFW_MOUSE_BUTTON_1}, 
    {Mouse::Right,   GLFW_MOUSE_BUTTON_2}, 
    {Mouse::Middle,  GLFW_MOUSE_BUTTON_3}, 
    {Mouse::Back,    GLFW_MOUSE_BUTTON_4}, 
    {Mouse::Forward, GLFW_MOUSE_BUTTON_5},
    {Mouse::_6,      GLFW_MOUSE_BUTTON_6},
    {Mouse::_7,      GLFW_MOUSE_BUTTON_7},
    {Mouse::_8,      GLFW_MOUSE_BUTTON_8},
  };
}