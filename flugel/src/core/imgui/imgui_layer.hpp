#pragma once

#include "core/layers/layer.hpp"

namespace fge {
  class FGE_API ImGuiLayer : public Layer {
  public:
    ImGuiLayer();

    bool onAppEvent(AppEvent& e) override;
    bool onRenderEvent(RenderEvent& e) override;
    bool onKeyboardEvent(KeyboardEvent& e) override;
    bool onMouseEvent(MouseEvent& e) override;
    
  private:
    App* app;
		bool blockInputEvents_{true};
    bool blockAppEvents_{false};
    u64 clickCount_{0};
    bool vsyncEnabled_{false};


    static void setDarkThemeColors();
  };
}