#include "window.hpp"

#if defined(WIN32)
  #include "platform/windows/windows_window.hpp"
#endif

namespace Flugel {
  Unique<Window> Window::create(const WindowProps& props) {
    #if defined(WIN32)
      return CreateUnique<WindowsWindow>(props);
    #endif
  }
}