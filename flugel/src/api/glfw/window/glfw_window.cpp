#include "glfw_window.hpp"

#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/input/input.hpp"

#include <glad/glad.h>

namespace fge {
  static uint8_t glfwWindowCount_s{0};

  static void glfwErrorCallback(int error, const char* message) {
    FGE_ERROR_ENG("GFLW Error {0} | {1}", error, message);
  }

  GlfwWindow::GlfwWindow(const WindowProperties& props)
    : Window{props} {
    init();
  }

  GlfwWindow::~GlfwWindow() {
    FGE_TRACE_ENG("Destructing GlfwWindow...");
    shutdown();
  }

  void GlfwWindow::init() {
    FGE_DEBUG_ENG("Creating window: {0} ({1}, {2})", data_.title, data_.windowDims.x, data_.windowDims.y);
    if (glfwWindowCount_s == 0) {
      int32_t glfwInitSuccess = glfwInit();
      FGE_ASSERT_ENG(glfwInitSuccess, "Failed to initialize GLFW!");
      glfwSetErrorCallback(glfwErrorCallback);
    }
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    FGE_INFO_ENG("Initialized GLFW {0}.{1}.{2}!", major, minor, revision);

    vidMode_ = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_DECORATED, !data_.customDecor);
    glfwWindow_ = glfwCreateWindow(
      (int32_t)data_.windowDims.x,
      (int32_t)data_.windowDims.y,
      data_.title.c_str(),
      nullptr,
      nullptr
    );
    ++glfwWindowCount_s;

    FGE_TRACE_ENG("Setting up GLFW window data!");
    setContextCurrent(true); // Set up glfw

    int32_t gladLoadSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    FGE_ASSERT_ENG(gladLoadSuccess, "Failed to initialize GLAD!");

    glfwSetWindowUserPointer(glfwWindow_, &data_);
    setVSync(data_.vSync);
    // ONLY run this if screen needs to start as fullscreen (otherwise errors!)
    //if (data_.fullScreen) {
      setFullscreen(data_.fullScreen);
    //}
    setCallbacks();

    setContextCurrent(false); // Prepare for context transfer to render thread
    FGE_TRACE_ENG("GLFW window data setup complete!");
  }

  void GlfwWindow::setCallbacks() {
    glfwSetWindowCloseCallback(glfwWindow_, [](GLFWwindow* window) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      WindowCloseEvent e{};
      data.eventCallback(e);
    });
    glfwSetWindowSizeCallback(glfwWindow_, [](GLFWwindow* window, int32_t width, int32_t height) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.windowDims = {width, height};
      WindowResizeEvent e{data.windowDims.x, data.windowDims.y};
      data.eventCallback(e);
    });
    glfwSetWindowPosCallback(glfwWindow_, [](GLFWwindow* window, int32_t xPos, int32_t yPos) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      data.windowPos = {xPos, yPos};
      WindowMovedEvent e{data.windowPos.x, data.windowPos.y};
      data.eventCallback(e);
    });

    // KEYBOARD
    glfwSetKeyCallback(glfwWindow_, [](GLFWwindow* window, int32_t key, int32_t scanCode, int32_t action, int32_t mods) {
      WindowState& data = *(WindowState*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          KeyboardEvent e{Key::Pressed, Key::fromNative(key), 0, Modifier::fromNativeBits(mods)};
          data.eventCallback(e);
          break;
        }
        case GLFW_REPEAT: {
          // GLFW doesn't provide a repeat count, so 1 will do for most use cases
          KeyboardEvent e{Key::Repeat, Key::fromNative(key), 1, Modifier::fromNativeBits(mods)};
          data.eventCallback(e);
        }
          break;
        case GLFW_RELEASE:{
          KeyboardEvent e{Key::Released, Key::fromNative(key), 0, Modifier::fromNativeBits(mods)};
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
          MouseEvent e{Mouse::Pressed, Mouse::fromNative(button), Modifier::fromNativeBits(mods)};
          data.eventCallback(e);
          break;
        }
        case GLFW_RELEASE:{
          MouseEvent e{Mouse::Released, Mouse::fromNative(button), Modifier::fromNativeBits(mods)};
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
      //FGE_DEBUG_ENG("Delta: ({0}, {1})", data.cursorDelta.x, data.cursorDelta.y);

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
  
  void GlfwWindow::dragWindow(vector2_t windowCursorOffset) {
    int32_t x, y;
    glfwGetWindowPos(glfwWindow_, &x, &y);
    setPos(x + glm::floor(Input::cursorPosX()) - windowCursorOffset.x, 
           y + glm::floor(Input::cursorPosY()) - windowCursorOffset.y);
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

  void GlfwWindow::setContextCurrent(bool current) {
    if (current) {
      FGE_DEBUG_ENG("Making GL context current to thread ID {0}", std::this_thread::get_id());
      glfwMakeContextCurrent(glfwWindow_);
    } else {
      FGE_DEBUG_ENG("Making GL context non-current!");
      glfwMakeContextCurrent(nullptr);
    }
  }
}