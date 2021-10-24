#pragma once

#include "layer.hpp"
#include "util/color/color.hpp"

namespace fge {
  class EngineLayer : public Layer {
  public:
    EngineLayer()
      : Layer{"fge_engine_layer"} {}
  private:
    vector2_t windowDragOffset_; // cursor position at time of clicking to drag window
    bool draggingWindowDecor_{false};
    bool closingWindowDecor_{false};

    // Rendering
    Color clearColor_{0x2D2A2AFF};
    
    virtual bool onAppEvent(AppEvent& e) override;
    virtual bool onRenderEvent(RenderEvent& e) override;
    virtual bool onWindowEvent(WindowEvent& e) override;
    virtual bool onKeyboardEvent(KeyboardEvent& e) override;
    virtual bool onMouseEvent(MouseEvent& e) override;
    virtual bool onCursorEvent(CursorEvent& e) override;
    virtual bool onScrollEvent(ScrollEvent& e) override;

    void pollCustomDecor(MouseEvent& e);
  };
}