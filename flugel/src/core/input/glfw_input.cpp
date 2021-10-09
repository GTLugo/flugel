#include "glfw_input.hpp"

#include "core/app.hpp"

#include <GLFW/glfw3.h>

namespace fge {
  bool GlfwInput::isKeyPressedImpl(Key::Code key) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    auto state = glfwGetKey(window, Key::toNative(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool GlfwInput::isMousePressedImpl(Mouse::Code button) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    auto state = glfwGetMouseButton(window, Mouse::toNative(button));
    return state == GLFW_PRESS;
  }

  vector2_t GlfwInput::cursorPosImpl() {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    vector2_t pos;
    glfwGetCursorPos(window, &pos.x, &pos.y);
    return pos;
  }

  double GlfwInput::cursorPosXImpl() {
    return cursorPosImpl().x;
  }

  double GlfwInput::cursorPosYImpl() {
    return cursorPosImpl().y;
  }
}