#include "window.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "core/window/glfw_window.hpp"
#endif


namespace Flugel {
  Unique<Window> Window::create(const WindowProperties& props) {
    #if defined(FLUGEL_USE_GLFW)
      return makeUnique<GlfwWindow>(props);
    #else
      FLUGEL_ASSERT_E(false, "Unsupported/unknown windowing library!");
      return nullptr;
    #endif
  }
}