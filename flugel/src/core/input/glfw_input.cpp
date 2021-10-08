#include "glfw_input.hpp"

#include "core/app.hpp"

#include <GLFW/glfw3.h>

namespace Flugel {
  bool GlfwInput::isKeyPressedImpl(int32_t key) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    auto state = glfwGetKey(window, key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool GlfwInput::isMousePressedImpl(int32_t button) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
  }

  double GlfwInput::cursorPosXImpl() {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    double xPos, _;
    glfwGetCursorPos(window, &xPos, &_);
    return xPos;
  }

  double GlfwInput::cursorPosYImpl() {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    double _, yPos;
    glfwGetCursorPos(window, &_, &yPos);
    return yPos;
  }
}