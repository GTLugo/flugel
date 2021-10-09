#include "mouse_codes.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "api/glfw/input/glfw_mousemap.hpp"
#endif

namespace fge {
  #if defined(FLUGEL_USE_GLFW)
    Unique<Mouse> Mouse::instance_ = makeUnique<GlfwMouse>();
  #else
    Unique<MouseMap> MouseMap::instance_ = nullptr;
  #endif
}