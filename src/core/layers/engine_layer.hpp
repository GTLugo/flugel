#pragma once

#include "layer.hpp"
#include "core/renderer/buffer/frame_buffer.hpp"

namespace ff {
  class EngineLayer final : public Layer {
  public:
    EngineLayer() : Layer{"fge_engine_layer"} {}
  private:
    vec2 windowDragOffset_{}; // cursor position at time of clicking to drag window
    bool draggingWindowDecor_{false};
    bool closingWindowDecor_{false};
    Color clearColor_{0x00FF00FF}; // 0x2D2A2AFF
    Shared<FrameBuffer> defaultFrameBuffer_;
    
    bool onAppEvent(const AppEvent& e) final;
    bool onRenderEvent(const RenderEvent& e) final;
    bool onWindowEvent(const WindowEvent& e) final;
    bool onKeyboardEvent(const KeyboardEvent& e) final;
    bool onMouseEvent(const MouseEvent& e) final;
    bool onCursorEvent(const CursorEvent& e) final;
    bool onScrollEvent(const ScrollEvent& e) final;

    void pollCustomDecor(const MouseEvent& e);
  };
}