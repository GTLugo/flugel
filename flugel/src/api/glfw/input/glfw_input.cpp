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

  bool Input::isPressed(Modifier::BitCodes bitCodes) {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    
    // Test each modifier individually. If any are not set in the set we are checking,
    // then the test should fail. Else, return true.
    if (bitCodes & Modifier::Shift) {
      if (glfwGetKey(window, Key::toNative(Key::LeftShift)) != GLFW_PRESS 
          && glfwGetKey(window, Key::toNative(Key::RightShift)) != GLFW_PRESS) {
        return false;
      }
    }
    if (bitCodes & Modifier::Control) {
      if (glfwGetKey(window, Key::toNative(Key::LeftControl)) != GLFW_PRESS 
          && glfwGetKey(window, Key::toNative(Key::RightControl)) != GLFW_PRESS) {
        return false;
      }
    }
    if (bitCodes & Modifier::Alt) {
      if (glfwGetKey(window, Key::toNative(Key::LeftAlt)) != GLFW_PRESS 
          && glfwGetKey(window, Key::toNative(Key::RightAlt)) != GLFW_PRESS) {
        return false;
      }
    }
    if (bitCodes & Modifier::Super) {
      if (glfwGetKey(window, Key::toNative(Key::LeftSuper)) != GLFW_PRESS 
          && glfwGetKey(window, Key::toNative(Key::RightSuper)) != GLFW_PRESS) {
        return false;
      }
    }
    if (bitCodes & Modifier::CapsLock) {
      if (glfwGetKey(window, Key::toNative(Key::CapsLock)) != GLFW_PRESS) {
        return false;
      }
    }
    if (bitCodes & Modifier::NumLock) {
      if (glfwGetKey(window, Key::toNative(Key::NumLock)) != GLFW_PRESS) {
        return false;
      }
    }

    return true;
  }

  vector2_t Input::cursorPos() {
    auto window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    vector2_t pos;
    glfwGetCursorPos(window, &pos.x, &pos.y);
    return pos;
  }
}

#endif // API GUARD