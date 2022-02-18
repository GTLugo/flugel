//
// Created by galex on 2/17/2022.
//
#pragma once

#include "core/renderer/render_dispatcher.hpp"

namespace fge {
  class OpenGLRenderDispatcher : public RenderDispatcher {
  public:
    void clear(Color color) final;
    void draw(const Shared<VertexArray>& vertexArray) final;
  };
}
