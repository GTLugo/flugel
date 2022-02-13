#pragma once

#include "layer.hpp"
#include "util/color/color.hpp"

namespace fge {
  class EngineLayer : public Layer {
  public:
    EngineLayer()
      : Layer{"fge_engine_layer"} {}
  private:
    vec2 windowDragOffset_{}; // cursor position at time of clicking to drag window
    bool draggingWindowDecor_{false};
    bool closingWindowDecor_{false};

    // Rendering
    Color clearColor_{0x2D2A2AFF};
    
    bool onAppEvent(AppEvent& e) override;
    bool onRenderEvent(RenderEvent& e) override;
    bool onWindowEvent(WindowEvent& e) override;
    bool onKeyboardEvent(KeyboardEvent& e) override;
    bool onMouseEvent(MouseEvent& e) override;
    bool onCursorEvent(CursorEvent& e) override;
    bool onScrollEvent(ScrollEvent& e) override;

    void pollCustomDecor(MouseEvent& e);
  };
}