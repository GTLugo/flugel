#include "windows_window.hpp"
#include "flugel/events/keyboard_event.hpp"
#include "flugel/events/mouse_event.hpp"
#include "flugel/events/window_event.hpp"
#include "flugel/events/app_event.hpp"

namespace Flugel {
  static bool isGLFWinitialized = false;

  WindowsWindow::WindowsWindow(const WindowProps& props) {
    init(props);
  }

  WindowsWindow::~WindowsWindow() {
    shut();
  }

  void WindowsWindow::init(const WindowProps& props) {
    FLUGEL_INFO_E(
      "Initializing window <{0}> ({1}, {2})", 
      props.title,
      props.width,
      props.height
    );

    data_.title = props.title;
    data_.width = props.width;
    data_.height = props.height;
    data_.vsync = props.vsync;

    if (!isGLFWinitialized) {
      int success = glfwInit();
      FLUGEL_ASSERT_E(success, "Failed to initialize GLFW!");
      glfwSetErrorCallback([](int error_code, const char description[]) {
        FLUGEL_ERROR_E("GLFW <{0}> ({1})", error_code, description);
      });
    }

    
    glfwWindow_ = glfwCreateWindow(
      data_.width, 
      data_.height, 
      data_.title.c_str(),
      nullptr,
      nullptr
    );
    glfwMakeContextCurrent(glfwWindow_);
    glfwSetWindowUserPointer(glfwWindow_, &data_);
    setVsync(data_.vsync);

    setGlfwCallbacks();
  }

  void WindowsWindow::shut() {
    glfwDestroyWindow(glfwWindow_);
  }

  void WindowsWindow::setGlfwCallbacks() {
    // APP

    // WINDOW
    glfwSetWindowCloseCallback(glfwWindow_, [](GLFWwindow* window) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      WindowCloseEvent event{};
      data.eventCallback(event);
    });
    glfwSetWindowSizeCallback(glfwWindow_, [](GLFWwindow* window, int width, int height) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.width = width;
      data.height = height;

      WindowResizeEvent event{data.width, data.height};
      data.eventCallback(event);
    });
    glfwSetWindowPosCallback(glfwWindow_, [](GLFWwindow* window, int xpos, int ypos) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      data.xPos = xpos;
      data.yPos = ypos;

      WindowMovedEvent event{data.xPos, data.yPos};
      data.eventCallback(event);
    });

    // KEYBOARD
    glfwSetKeyCallback(glfwWindow_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          KeyPressedEvent event{key, 0};
          data.eventCallback(event);
          break;
        }
        case GLFW_REPEAT: {
          KeyPressedEvent event{key, 1}; // GLFW doesn't provide a repeat count, so 1 will do for most use cases
          data.eventCallback(event);
        }
          break;
        case GLFW_RELEASE:{
          KeyReleasedEvent event{key};
          data.eventCallback(event);
          break;
        }
        default:
          break;
      }
    });

    // MOUSE
    glfwSetCursorPosCallback(glfwWindow_, [](GLFWwindow* window, double xpos, double ypos) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      MouseMovedEvent event{xpos, ypos};
      data.eventCallback(event);
    });
    glfwSetScrollCallback(glfwWindow_, [](GLFWwindow* window, double xoffset, double yoffset) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      MouseScrolledEvent event{xoffset, yoffset};
      data.eventCallback(event);
    });
    glfwSetMouseButtonCallback(glfwWindow_, [](GLFWwindow* window, int button, int action, int mods) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      switch (action) {
        case GLFW_PRESS: {
          MousePressedEvent event{button};
          data.eventCallback(event);
          break;
        }
        case GLFW_RELEASE:{
          MouseReleasedEvent event{button};
          data.eventCallback(event);
          break;
        }
        default:
          break;
      }
    });
  }

  void WindowsWindow::update() {
    glfwPollEvents();
    glfwSwapBuffers(glfwWindow_);
  }

  void WindowsWindow::setVsync(bool enabled) {
    if (enabled) {
      glfwSwapInterval(1);
    } else {
      glfwSwapInterval(0);
    }
    data_.vsync = enabled;
  }
}