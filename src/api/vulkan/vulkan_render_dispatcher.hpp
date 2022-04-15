//
// Created by galex on 4/14/2022.
//

#pragma once

#include "core/renderer/render_dispatcher.hpp"

namespace ff {
  class VulkanRenderDispatcher: public RenderDispatcher {
  public:
    void clear(Color color) final;
    void draw(const Shared<VertexArray>& vertexArray) final;
    void setDepthTest(bool enabled) final;
  };
}

