//
// Created by galex on 4/14/2022.
//

#pragma once

#include "core/renderer/context.hpp"

struct GLFWwindow;

namespace ff {
  class VulkanContext: public RenderContext {
  public:
    explicit VulkanContext(GLFWwindow* windowHandle);
    ~VulkanContext();

    virtual void* nativeContext() override { return nullptr; }
    void setCurrent(bool isCurrent) final;
    void swapBuffers() final;
  private:
    GLFWwindow* windowHandle_;
  };
}

