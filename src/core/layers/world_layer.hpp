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
    bool onMainEvent(const MainEvent& e) final;
    bool onGameEvent(const GameEvent& e) final;
    bool onWindowEvent(const WindowEvent& e) final;
    bool onInputEvent(const InputEvent& e) final;
  };
}

