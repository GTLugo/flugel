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
    FLUGEL_DEBUG_E("Making GL context current to thread ID {0}", std::this_thread::get_id());
  }

  void Window::makeContextNonCurrent() {
    glfwMakeContextCurrent(nullptr);
    FLUGEL_DEBUG_E("Making GL context non-current!");
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
      WindowCloseEvent e{};
      data.eventCallback(e);
    });
    glfwSetWindowSizeCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t width, int32_t height) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.width = width;
      data.height = height;
      WindowResizeEvent e{data.width, data.height};
      data.eventCallback(e);
    });
    glfwSetWindowPosCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t xPos, int32_t yPos) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.xPos = xPos;
      data.yPos = yPos;
      WindowMovedEvent e{data.xPos, data.yPos};
      data.eventCallback(e);
    });

    // KEYBOARD
    glfwSetKeyCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t key, int32_t scanCode, int32_t action, int32_t mods) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
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
    glfwSetMouseButtonCallback(glfwWindow_.get(), [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
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
    glfwSetCursorPosCallback(glfwWindow_.get(), [](GLFWwindow* window, double xPos, double yPos) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

      CursorEvent e{xPos, yPos};
      data.eventCallback(e);
    });
    glfwSetScrollCallback(glfwWindow_.get(), [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      ScrollEvent e{xOffset, yOffset};
      data.eventCallback(e);
    });
  }

  void Window::shutdown() {
    
  }
}