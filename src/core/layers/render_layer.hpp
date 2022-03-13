#pragma once

#include "layer.hpp"

#include "core/renderer/renderer.hpp"

namespace fge {
  class FGE_API RenderLayer : public Layer {
  public:
    RenderLayer()
      : Layer{"fge_render_layer"} {}
  private:
    // Rendering
    Color clearColor_{0x00FF00FF}; // 0x2D2A2AFF

    // App Frame
    Shared<VertexArray> frameQuad_;
    Shared<Shader> frameShader_;
    Shared<FrameBuffer> frameBuffer_;

    bool onRenderEvent(RenderEvent& e) override;
  };
}