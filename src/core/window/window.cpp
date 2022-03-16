#include "window.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "api/glfw/window/glfw_window.hpp"
#endif

#if defined(FLUGEL_USE_SDL2)
  #include "api/sdl2/window/sdl2_window.hpp"
#endif


namespace ff {
  Unique<Window> Window::create(const WindowProperties& props) {
    #if defined(FLUGEL_USE_GLFW)
      return makeUnique<GlfwWindow>(props);
    #elif defined(FLUGEL_USE_SDL2)
      return makeUnique<Sdl2Window>(props);
    #else
      FGE_ASSERT_ENG(false, "Unsupported/unknown windowing library!");
      return nullptr;
    #endif
  }
}