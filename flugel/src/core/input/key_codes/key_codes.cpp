#include "key_codes.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "glfw_key_mappings.hpp"
#endif

namespace fge {
  #if defined(FLUGEL_USE_GLFW)
    Unique<KeyMap> KeyMap::instance_ = makeUnique<GlfwKeyMap>();
  #else
    Unique<KeyMap> KeyMap::instance_ = nullptr;
  #endif
}