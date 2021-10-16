#include "opengl_context.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace fge {
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : windowHandle_{windowHandle} {
    FGE_ASSERT_ENG(windowHandle, "Window handle is nullptr!");
    init();
  }

  OpenGLContext::~OpenGLContext() {
    delete context_;
  }

  void OpenGLContext::init() {
    setCurrent(true);
    
    context_ = new GladGLContext();
    int32_t gladVersion = gladLoadGLContext(context_, glfwGetProcAddress);
    FGE_ASSERT_ENG(gladVersion, "Failed to initialize GLAD!");
    FGE_INFO_ENG("Using OpenGL | Vendor: {} | Renderer: {} | Version: {}.{}", 
      context_->GetString(GL_VENDOR),
      context_->GetString(GL_RENDERER),
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