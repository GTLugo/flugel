#include "opengl_context.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace fge {
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : windowHandle_{windowHandle} {
    FGE_ASSERT_ENG(windowHandle, "Window handle is nullptr!");
    init();
  }

  void OpenGLContext::init() {
    setCurrent(true);
    
    int32_t gladVersion = gladLoadGL(glfwGetProcAddress);
    FGE_ASSERT_ENG(gladVersion, "Failed to initialize GLAD!");
    FGE_INFO_ENG("Using OpenGL | Vendor: {} | Renderer: {} | Version: {}.{}", 
      glGetString(GL_VENDOR), 
      glGetString(GL_RENDERER),
      GLAD_VERSION_MAJOR(gladVersion),
      GLAD_VERSION_MINOR(gladVersion)
    );

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