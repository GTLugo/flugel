#include "key_codes.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "glfw_key_mappings.hpp"
#endif

namespace fge {
  #if defined(FLUGEL_USE_GLFW)
    Unique<Key> Key::instance_ = makeUnique<GlfwKey>();
    Unique<Modifier> Modifier::instance_ = makeUnique<GlfwModifier>();
  #else
    Unique<Key> Key::instance_ = nullptr;
    Unique<Modifier> Modifier::instance_ = nullptr;
  #endif
}