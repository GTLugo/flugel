#pragma once

#include "layer.hpp"
#include "core/renderer/vertex_array/vertex_array.hpp"
#include "core/renderer/shader.hpp"

#include "util/color/color.hpp"

namespace fge {
  class RenderLayer : public Layer {
  public:
    RenderLayer()
      : Layer{"fge_render_layer"} {}
  private:
    // Rendering
    Color clearColor_{0x2D2A2AFF};
    Shared<VertexArray> vao_;
    Shared<VertexArray> vaoSqr_;
    Shared<Shader> shader_;

    bool onRenderEvent(RenderEvent& e) override;
  };
}