#pragma once

#include "layer.hpp"

#include "core/renderer/renderer.hpp"

namespace ff {
  class RenderLayer : public Layer {
  public:
    RenderLayer() : Layer{"fge_render_layer"} {}
  private:
    // Rendering
    Color clearColor_{0x00FF00FF}; // 0x2D2A2AFF
    Shared<FrameBuffer> defaultFrameBuffer_;

    bool onRenderEvent(RenderEvent& e) override;
  };
}