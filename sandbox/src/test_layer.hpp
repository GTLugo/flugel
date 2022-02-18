#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer : public fge::Layer {
    using Input = fge::Input;
    using Key = fge::Key;
    using Modifier = fge::Modifier;
  public:
    TestLayer()
      : Layer{"test_layer"} {
      FGE_DEBUG("{}", fge::UUID{});
    }

    bool onRenderEvent(fge::RenderEvent& e) final;
    bool onLogicEvent(fge::LogicEvent& e) final;
    bool onMouseEvent(fge::MouseEvent& e) final;
    bool onKeyboardEvent(fge::KeyboardEvent& e) final;

  private:
    fge::Shared<fge::VertexArray> vao_;
    fge::Shared<fge::VertexArray> vaoSqr_;
    fge::Shared<fge::Shader> shader_;
  };
}