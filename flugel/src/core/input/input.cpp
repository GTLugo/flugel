#include "input.hpp"

#if defined(FLUGEL_USE_GLFW)
  #include "api/glfw/input/glfw_input.hpp"
#endif

namespace fge {
  #if defined(FLUGEL_USE_GLFW)
    Unique<Input> Input::instance_ = makeUnique<GlfwInput>();
  #else
    Unique<Input> Input::instance_ = nullptr;
  #endif
}