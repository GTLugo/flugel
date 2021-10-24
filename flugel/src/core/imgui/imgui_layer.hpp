#pragma once

#include "core/layers/layer.hpp"

namespace fge {
  class ImGuiLayer : public Layer {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual bool onAppEvent(AppEvent& e) override;
    virtual bool onRenderEvent(RenderEvent& e) override;
    
  private:
    void setDarkThemeColors();
  };
}