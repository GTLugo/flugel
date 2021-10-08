#pragma once

#include "core/layers/layer.hpp"

namespace Flugel {
  class ImGuiLayer : public Layer {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void attach();
    void detach();
  
    void render();
  };
}