//
// Created by galex on 4/14/2022.
//


#include "vulkan_context.hpp"

#include <GLFW/glfw3.h>

namespace ff {
  VulkanContext::VulkanContext(GLFWwindow* windowHandle)
      : windowHandle_{windowHandle} {
    FF_ASSERT_E(windowHandle, "Window handle is nullptr!");
    setCurrent(true);
    try {
      vk::ApplicationInfo appInfo{engName_.c_str(), VK_MAKE_VERSION(1, 0, 0), appName_.c_str(), VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_3};

      //TODO: This MIGHT be a memory leak, but i'm way too tired right now to figure out if it is or not
      // and even if it is, this is only called once theoretically, so it shouldn't be too bad of a leak. ;)
      u32 glfwExtensionCount{0};
      const char** glfwExtensions{glfwGetRequiredInstanceExtensions(&glfwExtensionCount)};
      std::vector<const char*> glfwExtensionVec{glfwExtensions, glfwExtensions + glfwExtensionCount};

      vk::InstanceCreateInfo instanceCreateInfo = vk::InstanceCreateInfo()
          .setPApplicationInfo(&appInfo)
          .setEnabledExtensionCount(glfwExtensionCount)
          .setPEnabledExtensionNames(glfwExtensionVec);

      std::vector<vk::ExtensionProperties> extensions{vk::enumerateInstanceExtensionProperties()};
      std::stringstream extensionStream{};
      for (const auto& ext: extensions) {
        extensionStream << '\t' << ext.extensionName << '\n';
      }
      Log::info_e("Available Vulkan Extensions: \n{}", extensionStream.str());

      instance_ = vk::createInstance(instanceCreateInfo);

      physicalDevice_ = instance_.enumeratePhysicalDevices().front();

    } catch (const vk::Error& e) {
      Log::critical_e("VULKAN ERROR: {}", e.what());
    } catch (const std::exception& e) {
      Log::critical_e("ERROR: {}", e.what());
    }

    setCurrent(false);
  }

  VulkanContext::~VulkanContext() {
    Log::trace_e("Destructing render context...");
    instance_.destroy();
  }

  void VulkanContext::swapBuffers() {

  }
}