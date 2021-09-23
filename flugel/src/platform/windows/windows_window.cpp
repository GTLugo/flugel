#include "windows_window.hpp"

namespace Flugel {
  static bool isGLFWinitialized = false;

  WindowsWindow::WindowsWindow(const WindowProps& props) {
    init(props);
  }

  WindowsWindow::~WindowsWindow() {
    shut();
  }

  void WindowsWindow::init(const WindowProps& props) {
    FLUGEL_INFO_ENGINE(
      "Initializing window <{0}>({1}, {2})", 
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
      FLUGEL_ASSERT_ENGINE(success, "Failed to initialize GLFW!");
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
  }

  void WindowsWindow::shut() {
    glfwDestroyWindow(glfwWindow_);
  }

  void WindowsWindow::onUpdate() {
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