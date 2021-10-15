#include "opengl_context.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace fge {
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : windowHandle_{windowHandle} {
    FGE_ASSERT_ENG(windowHandle, "Window handle is nullptr!");
    init();
  }

  void OpenGLContext::init() {
    setCurrent(true);
    int32_t gladLoadSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    FGE_ASSERT_ENG(gladLoadSuccess, "Failed to initialize GLAD!");
    setCurrent(false);
  }

  void OpenGLContext::setCurrent(bool isCurrent) {
    if (isCurrent) {
      FGE_DEBUG_ENG("Making GL context current to thread: {}", std::this_thread::get_id());
      glfwMakeContextCurrent(windowHandle_);
    } else {
      FGE_DEBUG_ENG("Making GL context non-current to thread: {}", std::this_thread::get_id());
      glfwMakeContextCurrent(nullptr);
    }
  }

  void OpenGLContext::swapBuffers() {
    glfwSwapBuffers(windowHandle_);
  }
}