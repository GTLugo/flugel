#if defined(FLUGEL_USE_GLFW) // API GUARD

#include "core/input/input.hpp"

#include "core/app.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  bool Input::isPressed(Key::Code key) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    auto state = glfwGetKey(window, Key::toNative(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool Input::isPressed(Mouse::Code button) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    auto state = glfwGetMouseButton(window, Mouse::toNative(button));
    return state == GLFW_PRESS;
  }

  vector2_t Input::cursorPos() {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    vector2_t pos;
    glfwGetCursorPos(window, &pos.x, &pos.y);
    return pos;
  }

  double Input::cursorPosX() {
    return cursorPos().x;
  }

  double Input::cursorPosY() {
    return cursorPos().y;
  }
}

#endif // API GUARD