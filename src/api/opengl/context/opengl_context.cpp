#include "opengl_context.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ff {
  void GLAPIENTRY messageCallback(GLenum source,
                                  GLenum type,
                                  GLuint id,
                                  GLenum severity,
                                  GLsizei length,
                                  const GLchar* message,
                                  const void* userParam ) {
    switch (type) {
      case GL_DEBUG_TYPE_ERROR: { 
        Log::debug_e("OPENGL ERROR | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: {
        Log::debug_e("OPENGL DEPRECATED BEHAVIOR | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: {
        Log::debug_e("OPENGL UNDEFINED BEHAVIOR | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_PORTABILITY: {
        Log::debug_e("OPENGL PORTABILITY | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      case GL_DEBUG_TYPE_PERFORMANCE: {
        Log::debug_e("OPENGL PERFORMANCE | Type: {0} | Severity: {1} | {2}", type, severity, message);
        return;
      }
      default: { return; }
    }
  }

  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : windowHandle_{windowHandle} {
    FF_ASSERT_E(windowHandle, "Window handle is nullptr!");
    setCurrent(true);

    context_ = new GladGLContext();
    i32 gladVersion = gladLoadGLContext(context_, glfwGetProcAddress);
    //gladSetGLContext(context_);
    //i32 gladVersion = gladLoadGL(glfwGetProcAddress);
    FF_ASSERT_E(gladVersion, "Failed to initialize GLAD!");
    Log::info_e("Using OpenGL | Vendor: {} | Renderer: {} | Version: {}.{}",
                 context_->GetString(GL_VENDOR),
                 context_->GetString(GL_RENDERER),
                 GLAD_VERSION_MAJOR(gladVersion),
                 GLAD_VERSION_MINOR(gladVersion)
    );

    context_->Enable(GL_FRAMEBUFFER_SRGB);
    #if defined(DEBUG) || defined(RELDEB)
    context_->Enable(GL_DEBUG_OUTPUT);
    context_->DebugMessageCallback(messageCallback, 0);
    #endif

    setCurrent(false);
  }

  OpenGLContext::~OpenGLContext() {
    Log::trace_e("Destructing render context...");
    delete context_;
  }

  void OpenGLContext::setCurrent(bool isCurrent) {
    if (isCurrent) {
      //Log::debug_e("Making GL context current to thread: {}", std::this_thread::get_id());
      glfwMakeContextCurrent(windowHandle_);
    } else {
      //Log::debug_e("Making GL context non-current to thread: {}", std::this_thread::get_id());
      glfwMakeContextCurrent(nullptr);
    }
  }

  void OpenGLContext::swapBuffers() {
    glfwSwapBuffers(windowHandle_);
  }
}