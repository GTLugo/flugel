#include "glfw_window.hpp"

#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/input/input.hpp"

#include <glad/glad.h>

namespace Flugel {
  static uint8_t glfwWindowCount_s{0};

  static void glfwErrorCallback(int error, const char* message) {
    FLUGEL_ERROR_E("GFLW Error {0} | {1}", error, message);
  }

  GlfwWindow::GlfwWindow(const WindowProperties& props)
    : Window{props} {
    init();
  }

  GlfwWindow::~GlfwWindow() {
    FLUGEL_TRACE_E("Destructing GlfwWindow...");
    shutdown();
    FLUGEL_TRACE_E("Destructed GlfwWindow!");
  }

  void GlfwWindow::init() {
    FLUGEL_DEBUG_E("Creating window: {0} ({1}, {2})", data_.title, data_.width, data_.height);
    if (glfwWindowCount_s == 0) {
      int32_t glfwInitSuccess = glfwInit();
      FLUGEL_ASSERT_E(glfwInitSuccess, "Failed to initialize GLFW!");
      glfwSetErrorCallback(glfwErrorCallback);
    }
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    FLUGEL_INFO_E("Initialized GLFW {0}.{1}.{2}!", major, minor, revision);

    vidMode_ = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_DECORATED, !data_.customDecor);
    glfwWindow_ = glfwCreateWindow(
      (int32_t)data_.width,
      (int32_t)data_.height,
      data_.title.c_str(),
      nullptr,
      nullptr
    );
    ++glfwWindowCount_s;

    FLUGEL_TRACE_E("Setting up GLFW window data!");
    setContextCurrent(true); // Set up glfw

    int32_t gladLoadSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    FLUGEL_ASSERT_E(gladLoadSuccess, "Failed to initialize GLAD!");

    glfwSetWindowUserPointer(glfwWindow_, &data_);
    setVSync(data_.vSync);
    // ONLY run this if screen needs to start as fullscreen (otherwise errors!)
    if (data_.fullScreen) {
      setFullscreen(true);
    }
    setCallbacks();

    setContextCurrent(false); // Prepare for context transfer to render thread
    FLUGEL_TRACE_E("GLFW window data setup complete!");
  }

  void GlfwWindow::setCallbacks() {
    glfwSetWindowCloseCallback(glfwWindow_, [](GLFWwindow* window) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      WindowCloseEvent e{};
      data.eventCallback(e);
    });
    glfwSetWindowSizeCallback(glfwWindow_, [](GLFWwindow* window, int32_t width, int32_t height) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.width = width;
      data.height = height;
      WindowResizeEvent e{data.width, data.height};
      data.eventCallback(e);
    });
    glfwSetWindowPosCallback(glfwWindow_, [](GLFWwindow* window, int32_t xPos, int32_t yPos) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.xPos = xPos;
      data.yPos = yPos;
      WindowMovedEvent e{data.xPos, data.yPos};
      data.eventCallback(e);
    });

    // KEYBOARD
    glfwSetKeyCallback(glfwWindow_, [](GLFWwindow* window, int32_t key, int32_t scanCode, int32_t action, int32_t mods) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          KeyboardEvent e{ButtonState::Pressed, key, 0, (KeyModifiers)mods};
          data.eventCallback(e);
          break;
        }
        case GLFW_REPEAT: {
          // GLFW doesn't provide a repeat count, so 1 will do for most use cases
          KeyboardEvent e{ButtonState::Pressed, key, 1, (KeyModifiers)mods};
          data.eventCallback(e);
        }
          break;
        case GLFW_RELEASE:{
          KeyboardEvent e{ButtonState::Released, key, 0, (KeyModifiers)mods};
          data.eventCallback(e);
          break;
        }
        default:
          break;
      }
    });

    // MOUSE
    glfwSetMouseButtonCallback(glfwWindow_, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          MouseEvent e{ButtonState::Pressed, button};
          data.eventCallback(e);
          break;
        }
        case GLFW_RELEASE:{
          MouseEvent e{ButtonState::Released, button};
          data.eventCallback(e);
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
      //FLUGEL_DEBUG_E("Delta: ({0}, {1})", data.cursorDelta.x, data.cursorDelta.y);

      CursorEvent e{xPos, yPos};
      data.eventCallback(e);
    });
    glfwSetScrollCallback(glfwWindow_, [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      ScrollEvent e{xOffset, yOffset};
      data.eventCallback(e);
    });
  }

  void GlfwWindow::shutdown() {
    glfwDestroyWindow(glfwWindow_);
    --glfwWindowCount_s;
    if (glfwWindowCount_s == 0) {
      glfwTerminate();
    }
  }

  void GlfwWindow::pollEvents() {
    glfwPollEvents();
  }
  
  void GlfwWindow::render() {
    glfwSwapBuffers(glfwWindow_);
    glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  
  void GlfwWindow::dragWindow(double cursorOffsetX, double cursorOffsetY) {
    int32_t x, y;
    glfwGetWindowPos(glfwWindow_, &x, &y);
    setPos(x + glm::floor(Input::cursorPosX()) - cursorOffsetX, 
           y + glm::floor(Input::cursorPosY()) - cursorOffsetY);
  }

  void GlfwWindow::setIcon(uint8_t* image, int32_t width, int32_t height) {
    icons_[0] = GLFWimage{width, height, image};
    glfwSetWindowIcon(glfwWindow_, 1, icons_);
  }

  void GlfwWindow::setPos(double xPos, double yPos) {
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
      data_.xPosBeforeFullscreen = data_.xPos;
      data_.yPosBeforeFullscreen = data_.yPos;
      data_.widthBeforeFullscreen = data_.width;
      data_.heightBeforeFullscreen = data_.height;
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
                           data_.xPosBeforeFullscreen,
                           data_.yPosBeforeFullscreen,
                           data_.widthBeforeFullscreen,
                           data_.heightBeforeFullscreen,
                           0);
    }
    data_.fullScreen = enabled;
  }

  void GlfwWindow::setContextCurrent(bool current) {
    if (current) {
      FLUGEL_DEBUG_E("Making GL context current to thread ID {0}", std::this_thread::get_id());
      glfwMakeContextCurrent(glfwWindow_);
    } else {
      FLUGEL_DEBUG_E("Making GL context non-current!");
      glfwMakeContextCurrent(nullptr);
    }
  }
}