#include "window.hpp"

#if defined(WIN32)
  #include "platform/windows/windows_window.hpp"
#endif

namespace Flugel {
  Unique<Window> Window::create(const WindowProps& props) {
    #if defined(WIN32)
      return CreateUnique<WindowsWindow>(props);
    #else
      FLUGEL_ERROR_E("FLUGEL CURRENTLY ONLY SUPPORTS GLFW WINDOWS (WINDOWS ONLY)");
    #endif
  }
}