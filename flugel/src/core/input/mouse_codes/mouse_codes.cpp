#include "mouse_codes.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "glfw_mouse_mappings.hpp"
#endif

namespace fge {
  #if defined(FLUGEL_USE_GLFW)
    Unique<MouseMap> MouseMap::instance_ = makeUnique<GlfwMouseMap>();
  #else
    Unique<MouseMap> MouseMap::instance_ = nullptr;
  #endif
}