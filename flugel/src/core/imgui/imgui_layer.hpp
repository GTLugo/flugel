#pragma once

#include "core/layers/layer.hpp"

namespace fge {
  class ImGuiLayer : public Layer {
  public:
    ImGuiLayer();

    bool onAppEvent(AppEvent& e) override;
    bool onRenderEvent(RenderEvent& e) override;
    bool onKeyboardEvent(KeyboardEvent& e) override;
    bool onMouseEvent(MouseEvent& e) override;
    
  private:
		bool blockInputEvents_{true};
    bool blockAppEvents_{false};

    static void setDarkThemeColors();
  };
}