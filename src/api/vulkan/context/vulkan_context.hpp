//
// Created by galex on 4/14/2022.
//

#pragma once

#include "core/renderer/context.hpp"

#include <vulkan/vulkan.hpp>

struct GLFWwindow;

namespace ff {
  class VulkanContext: public RenderContext {
    const std::string appName_ = "Flugel Application";
    const std::string engName_ = "Flugel Framework";
  public:
    explicit VulkanContext(GLFWwindow* windowHandle);
    ~VulkanContext();

    void* commandBuffer() override { return nullptr; }
    void* pipeline() override { return nullptr; }
    void* nativeContext() override { return nullptr; }
    void setCurrent(bool isCurrent) final {} // vulkan doesn't have a sense of state like OpenGL, so this is unnecessary
    void swapBuffers() final;
  private:
    GLFWwindow* windowHandle_;
    vk::Instance instance_;
    vk::PhysicalDevice physicalDevice_;
  };
}

