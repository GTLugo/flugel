//
// Created by galex on 4/2/2022.
//
#pragma once

#include "layer.hpp"
#include "core/renderer/buffer/frame_buffer.hpp"

namespace ff {
  class WorldLayer final : public Layer {
  public:
    WorldLayer() : Layer{"world_layer"} {}

  private:
    bool onAppEvent(const AppEvent& e) final;
    bool onLogicEvent(const LogicEvent& e) final;
    bool onRenderEvent(const RenderEvent& e) final;
    bool onWindowEvent(const WindowEvent& e) final;
    bool onKeyboardEvent(const KeyboardEvent& e) final;
    bool onMouseEvent(const MouseEvent& e) final;
    bool onCursorEvent(const CursorEvent& e) final;
    bool onScrollEvent(const ScrollEvent& e) final;
  };
}

