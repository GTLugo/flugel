#include "window.hpp"

namespace Flugel {
  bool Window::isGlfwInitialized_{false};

  Window::Window(const WindowProperties& props)
    : data_{props} {
    init();
  }

  Window::~Window() {
    shutdown();
  }

  void Window::makeContextCurrent() {
    glfwMakeContextCurrent(glfwWindow_.get());
    FLUGEL_INFO_E("Making GL context current!");
  }

  void Window::makeContextNonCurrent() {
    glfwMakeContextCurrent(nullptr);
    FLUGEL_INFO_E("Making GL context non-current!");
  }

  void Window::processInput() {
    glfwPollEvents();
  }
  
  void Window::swapBuffers() {
    glfwSwapBuffers(glfwWindow_.get());
    glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Window::setPos(int32_t xPos, int32_t yPos) {
    glfwSetWindowPos(glfwWindow_.get(), xPos, yPos);
  }

  void Window::setVSync(bool enabled) {
    if (enabled) {
      glfwSwapInterval(1);
    } else {
      glfwSwapInterval(0);
    }
    data_.vSync = enabled;
  }

  void Window::init() {
    FLUGEL_DEBUG_E("Creating window: {0} ({1}, {2})", data_.title, data_.width, data_.height);

    if (!isGlfwInitialized_) {
      int32_t success = glfwInit();
      FLUGEL_ASSERT_E(success, "Failed to initialize GLFW!");
      isGlfwInitialized_ = true;
    }
    FLUGEL_INFO_E("Initialized GLFW!");

    glfwWindow_ = UniqueGlfwWindow{glfwCreateWindow(
      (int32_t)data_.width,
      (int32_t)data_.height,
      data_.title.c_str(),
      nullptr,
      nullptr
    )};

    FLUGEL_TRACE_E("Setting up GLFW window data!");
    makeContextCurrent(); // Set up glfw

    glfwSetWindowUserPointer(glfwWindow_.get(), &data_);
    setVSync(data_.vSync);
    setCallbacks();

    makeContextNonCurrent(); // Prepare for context transfer to render thread
    FLUGEL_TRACE_E("GLFW window data setup complete!");
  }

  void Window::setCallbacks() {
    glfwSetWindowCloseCallback(glfwWindow_.get(), [](GLFWwindow* window) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.windowCloseNotifier.notify({});
    });
    glfwSetWindowSizeCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t width, int32_t height) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.width = width;
      data.height = height;
      data.windowResizeNotifier.notify({data.width, data.height});
    });
    glfwSetWindowPosCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t xPos, int32_t yPos) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.xPos = xPos;
      data.yPos = yPos;
      data.windowMovedNotifier.notify({data.xPos, data.yPos});
    });

    // KEYBOARD
    glfwSetKeyCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int mods) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          data.keyPressedNotifier.notify({key, 0});
          break;
        }
        case GLFW_REPEAT: {
          // GLFW doesn't provide a repeat count, so 1 will do for most use cases
          data.keyPressedNotifier.notify({key, 1});
        }
          break;
        case GLFW_RELEASE:{
          data.keyReleasedNotifier.notify({key});
          break;
        }
        default:
          break;
      }
    });

    // MOUSE
    glfwSetMouseButtonCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          data.mousePressedNotifier.notify({button});
          break;
        }
        case GLFW_RELEASE:{
          data.mouseReleasedNotifier.notify({button});
          break;
        }
        default:
          break;
      }
    });
    glfwSetCursorPosCallback(glfwWindow_.get(), [](GLFWwindow* window, double xPos, double yPos) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.mouseMovedNotifier.notify({xPos, yPos});
    });
    glfwSetScrollCallback(glfwWindow_.get(), [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.mouseScrolledNotifier.notify({xOffset, yOffset});
    });
  }

  void Window::shutdown() {
    
  }
}