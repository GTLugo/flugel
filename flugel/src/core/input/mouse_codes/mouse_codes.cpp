#include "mouse_codes.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "glfw_mouse_mappings.hpp"
#endif

namespace fge {
  #if defined(FLUGEL_USE_GLFW)
    Unique<Mouse> Mouse::instance_ = makeUnique<GlfwMouse>();
  #else
    Unique<MouseMap> MouseMap::instance_ = nullptr;
  #endif
}