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

  void Window::processInput() {
    glfwPollEvents();
  }
  
  void Window::swapBuffers() {
    glfwSwapBuffers(glfwWindow_.get());
    glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
    glClear(GL_COLOR_BUFFER_BIT);
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
      int success = glfwInit();
      FLUGEL_ASSERT_E(success, "Failed to initialize GLFW!");
      isGlfwInitialized_ = true;
    }

    glfwWindow_ = UniqueGlfwWindow{glfwCreateWindow(
      (int)data_.width,
      (int)data_.height,
      data_.title.c_str(),
      nullptr,
      nullptr
    )};
    glfwMakeContextCurrent(glfwWindow_.get());
    glfwSetWindowUserPointer(glfwWindow_.get(), &data_);

    setVSync(data_.vSync);

    glfwSetWindowCloseCallback(glfwWindow_.get(), [](GLFWwindow* window) {
      WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
      WindowCloseEvent e{};
      data.closeNotifier.notify(e);
    });
  }

  void Window::shutdown() {
    
  }
}