#include "window.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "core/window/glfw_window.hpp"
#endif


namespace fge {
  Unique<Window> Window::create(const WindowProperties& props) {
    #if defined(FLUGEL_USE_GLFW)
      return makeUnique<GlfwWindow>(props);
    #else
      FGE_ASSERT_ENG(false, "Unsupported/unknown windowing library!");
      return nullptr;
    #endif
  }
}