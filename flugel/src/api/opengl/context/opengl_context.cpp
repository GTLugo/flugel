#include "opengl_context.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace fge {
  void GLAPIENTRY messageCallback(GLenum source,
                                  GLenum type,
                                  GLuint id,
                                  GLenum severity,
                                  GLsizei length,
                                  const GLchar* message,
                                  const void* userParam ) {
    switch (type) {
      case GL_DEBUG_TYPE_ERROR: { 
        FGE_ERROR_ENG("OPENGL ERROR | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: {
        FGE_ERROR_ENG("OPENGL DEPRECATED BEHAVIOR | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: {
        FGE_ERROR_ENG("OPENGL UNDEFINED BEHAVIOR | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_PORTABILITY: {
        FGE_ERROR_ENG("OPENGL PORTABILITY | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_PERFORMANCE: {
        FGE_ERROR_ENG("OPENGL PERFORMANCE | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      default: { return; }
    };
  }

  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : windowHandle_{windowHandle} {
    FGE_ASSERT_ENG(windowHandle, "Window handle is nullptr!");
    init();
  }

  OpenGLContext::~OpenGLContext() {
    //delete context_;
  }

  void OpenGLContext::init() {
    setCurrent(true);
    
    //context_ = new GladGLContext();
    //i32 gladVersion = gladLoadGLContext(context_, glfwGetProcAddress);
    i32 gladVersion = gladLoadGL(glfwGetProcAddress);
    FGE_ASSERT_ENG(gladVersion, "Failed to initialize GLAD!");
    FGE_INFO_ENG("Using OpenGL | Vendor: {} | Renderer: {} | Version: {}.{}", 
      glGetString(GL_VENDOR),
      glGetString(GL_RENDERER),
      GLAD_VERSION_MAJOR(gladVersion),
      GLAD_VERSION_MINOR(gladVersion)
    );
    //gladSetGLContext(context_);

    glEnable(GL_FRAMEBUFFER_SRGB);
    #if defined(DEBUG) || defined(RELDEB)
      glEnable(GL_DEBUG_OUTPUT);
      glDebugMessageCallback(messageCallback, 0);
    #endif

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