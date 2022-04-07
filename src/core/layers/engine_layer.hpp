#pragma once

#include "layer.hpp"
#include "core/renderer/buffer/frame_buffer.hpp"

namespace ff {
  class EngineLayer final : public Layer {
  public:
    EngineLayer() : Layer{"engine_layer"} {}
  private:
    vec2 windowDragOffset_{}; // cursor position at time of clicking to drag window
    bool draggingWindowDecor_{false};
    bool closingWindowDecor_{false};
    Color clearColor_{0x696969FF}; // 0x2D2A2AFF
    Shared<FrameBuffer> defaultFrameBuffer_;

    bool onMainEvent(const MainEvent& e) final;
    bool onGameEvent(const GameEvent& e) final;
    bool onWindowEvent(const WindowEvent& e) final;
    bool onInputEvent(const InputEvent& e) final;

    void pollCustomDecor(const InputMouseEvent& e);
  };
}