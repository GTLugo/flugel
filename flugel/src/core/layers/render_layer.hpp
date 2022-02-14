#pragma once

#include "layer.hpp"
#include "core/renderer/vertex_array/vertex_array.hpp"
#include "core/renderer/shader.hpp"

namespace fge {
  class RenderLayer : public Layer {
  public:
    RenderLayer()
      : Layer{"fge_render_layer"} {}
  private:
    // Rendering
    Shared<VertexArray> vao_;
    Shared<VertexArray> vaoSqr_;
    Shared<Shader> shader_;

    bool onRenderEvent(RenderEvent& e) override;
  };
}