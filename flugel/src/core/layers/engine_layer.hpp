#pragma once

#include "layer.hpp"
#include "util/color/color.hpp"
#include "core/renderer/vertex_array/vertex_array.hpp"
#include "core/renderer/shader.hpp"

namespace fge {
  class EngineLayer : public Layer {
  public:
    EngineLayer()
      : Layer{"flugel_game_engine"} {}
  private:
    vector2_t windowDragOffset_; // cursor position at time of clicking to drag window
    bool draggingWindowDecor_{false};
    bool closingWindowDecor_{false};

    // Rendering
    Color clearColor_{0x2D2A2AFF};
    Shared<VertexArray> vao_;
    Shared<VertexArray> vaoSqr_;
    Shared<Shader> shader_;
    
    virtual bool onAppEvent(AppEvent& e) override;
    virtual bool onWindowEvent(WindowEvent& e) override;
    virtual bool onKeyboardEvent(KeyboardEvent& e) override;
    virtual bool onMouseEvent(MouseEvent& e) override;
    virtual bool onCursorEvent(CursorEvent& e) override;
    virtual bool onScrollEvent(ScrollEvent& e) override;

    void pollCustomDecor(MouseEvent& e);
  };
}