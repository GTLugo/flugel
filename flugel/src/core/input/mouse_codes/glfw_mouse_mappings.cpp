#include "glfw_mouse_mappings.hpp"

#include "GLFW/glfw3.h"

namespace fge {
  std::map<MouseButton, int32_t> GlfwMouseMap::mouseMap_{
    {MouseButton::Unknown, -1},
    {MouseButton::Left,    GLFW_MOUSE_BUTTON_1}, 
    {MouseButton::Right,   GLFW_MOUSE_BUTTON_2}, 
    {MouseButton::Middle,  GLFW_MOUSE_BUTTON_3}, 
    {MouseButton::Back,    GLFW_MOUSE_BUTTON_4}, 
    {MouseButton::Forward, GLFW_MOUSE_BUTTON_5},
    {MouseButton::_6,      GLFW_MOUSE_BUTTON_6},
    {MouseButton::_7,      GLFW_MOUSE_BUTTON_7},
    {MouseButton::_8,      GLFW_MOUSE_BUTTON_8},
  };
}