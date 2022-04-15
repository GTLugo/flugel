//
// Created by galex on 4/14/2022.
//

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include "vulkan_context.hpp"

namespace ff {
  VulkanContext::VulkanContext(GLFWwindow* windowHandle)
      : windowHandle_{windowHandle} {
    FF_ASSERT_E(windowHandle, "Window handle is nullptr!");
    setCurrent(true);

    setCurrent(false);
  }

  VulkanContext::~VulkanContext() {
    Log::trace_e("Destructing render context...");

  }

  void VulkanContext::setCurrent(bool isCurrent) {
    if (isCurrent) {

    } else {

    }
  }

  void VulkanContext::swapBuffers() {

  }
}