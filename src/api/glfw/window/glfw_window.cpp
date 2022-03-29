#include "glfw_window.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/context/opengl_context.hpp"
#endif

#include "core/input/input.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"

namespace ff {

  static void glfwErrorCallback(int error, const char* message) {
    Log::debug_e("GFLW Error {0} | {1}", error, message);
  }

  GlfwWindow::GlfwWindow(const WindowProperties& props)
    : Window{props} {
    init();
  }

  GlfwWindow::~GlfwWindow() {
    Log::trace_e("Destructing GlfwWindow...");
    shutdown();
  }

  void GlfwWindow::init() {
    Log::trace_e("Creating window...");
    if (glfwWindowCount_ == 0) {
      i32 glfwInitSuccess = glfwInit();
      FF_ASSERT_E(glfwInitSuccess, "Failed to initialize GLFW!");
      glfwSetErrorCallback(glfwErrorCallback);
    }
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    Log::info_e("Using GLFW {}.{}.{}!", major, minor, revision);

    vidMode_ = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_DECORATED, !data_.customDecor);
    glfwWindow_ = glfwCreateWindow(
      (i32)data_.windowDims.x,
      (i32)data_.windowDims.y,
      data_.title.c_str(),
      nullptr,
      nullptr
    );
    ++glfwWindowCount_;

    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        context_ = makeUnique<OpenGLContext>(glfwWindow_);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
    context_->setCurrent(true);

    glfwSetWindowUserPointer(glfwWindow_, &data_);
    setVSync(data_.vSync);
    setFullscreen(data_.fullScreen);
    setCallbacks();

    context_->setCurrent(false); // Prepare for context transfer to render thread
    Log::debug_e("Created window: {} ({}, {})", data_.title, data_.windowDims.x, data_.windowDims.y);
  }

  void GlfwWindow::setCallbacks() {
    glfwSetWindowCloseCallback(glfwWindow_, [](GLFWwindow* window) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.eventCallback(WindowCloseEvent{});
    });
    glfwSetWindowSizeCallback(glfwWindow_, [](GLFWwindow* window, i32 width, i32 height) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.windowDims = {width, height};
      data.eventCallback(WindowResizeEvent{data.windowDims.x, data.windowDims.y});
    });
    glfwSetWindowPosCallback(glfwWindow_, [](GLFWwindow* window, i32 xPos, i32 yPos) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.windowPos = {xPos, yPos};
      data.eventCallback(WindowMovedEvent{data.windowPos.x, data.windowPos.y});
    });

    // KEYBOARD
    glfwSetKeyCallback(glfwWindow_, [](GLFWwindow* window, i32 key, i32 scanCode, i32 action, i32 mods) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          data.eventCallback(KeyboardEvent{Key::Pressed, Key::fromNative(key), 0, Modifier::fromNativeBits(mods)});
          break;
        }
        case GLFW_REPEAT: {
          // GLFW doesn't provide a repeat count, so 1 will do for most use cases
          data.eventCallback(KeyboardEvent{Key::Repeat, Key::fromNative(key), 1, Modifier::fromNativeBits(mods)});
        }
          break;
        case GLFW_RELEASE:{
          data.eventCallback(KeyboardEvent{Key::Released, Key::fromNative(key), 0, Modifier::fromNativeBits(mods)});
          break;
        }
        default:
          break;
      }
    });

    // MOUSE
    glfwSetMouseButtonCallback(glfwWindow_, [](GLFWwindow* window, i32 button, i32 action, i32 mods) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          data.eventCallback(MouseEvent{Mouse::Pressed, Mouse::fromNative(button), Modifier::fromNativeBits(mods)});
          break;
        }
        case GLFW_RELEASE:{
          data.eventCallback(MouseEvent{Mouse::Released, Mouse::fromNative(button), Modifier::fromNativeBits(mods)});
          break;
        }
        default:
          break;
      }
    });
    glfwSetCursorPosCallback(glfwWindow_, [](GLFWwindow* window, double xPos, double yPos) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.cursorPosOld = data.cursorPos;
      data.cursorPos = {xPos, yPos};
      data.cursorDelta = data.cursorPos - data.cursorPosOld;
      //Log::debug_e("Delta: ({0}, {1})", data.cursorDelta.x, data.cursorDelta.y);

      data.eventCallback(CursorEvent{xPos, yPos});
    });
    glfwSetScrollCallback(glfwWindow_, [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.eventCallback(ScrollEvent{xOffset, yOffset});
    });
  }

  void GlfwWindow::shutdown() {
    glfwDestroyWindow(glfwWindow_);
    --glfwWindowCount_;
    if (glfwWindowCount_ == 0) {
      glfwTerminate();
    }
  }

  void GlfwWindow::pollEvents() {
    glfwPollEvents();
  }
  
  void GlfwWindow::dragWindow(ivec2 windowCursorOffset) {
    i32 x, y;
    glfwGetWindowPos(glfwWindow_, &x, &y);
    setPos(static_cast<i32>(x + glm::floor(Input::cursorPos().x) - windowCursorOffset.x),
           static_cast<i32>(y + glm::floor(Input::cursorPos().y) - windowCursorOffset.y));
  }

  void GlfwWindow::setIcon(u8* image, i32 width, i32 height) {
    icons_[0] = GLFWimage{width, height, image};
    glfwSetWindowIcon(glfwWindow_, 1, icons_);
  }

  void GlfwWindow::setPos(i32 xPos, i32 yPos) {
    glfwSetWindowPos(glfwWindow_, xPos, yPos);
  }

  void GlfwWindow::setVSync(bool enabled) {
    if (enabled) {
      glfwSwapInterval(1);
    } else {
      glfwSwapInterval(0);
    }
    data_.vSync = enabled;
  }

  void GlfwWindow::setFullscreen(bool enabled) {
    if (enabled) {
      data_.posBeforeFullscreen = data_.windowPos;
      data_.dimsBeforeFullscreen = data_.windowDims;
      glfwSetWindowMonitor(glfwWindow_, 
                           glfwGetPrimaryMonitor(),
                           0,
                           0,
                           vidMode_->width,
                           vidMode_->height,
                           vidMode_->refreshRate);
    } else {
      glfwSetWindowMonitor(glfwWindow_,
                           nullptr,
                           data_.posBeforeFullscreen.x,
                           data_.posBeforeFullscreen.y,
                           data_.dimsBeforeFullscreen.x,
                           data_.dimsBeforeFullscreen.y,
                           0);
    }
    data_.fullScreen = enabled;
  }

  //void GlfwWindow::setContextCurrent(bool isCurrent) {
  //  context_->setContextCurrent(isCurrent);
  //}
}