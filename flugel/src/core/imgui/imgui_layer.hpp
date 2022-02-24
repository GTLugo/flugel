#pragma once

#include "core/layers/layer.hpp"
#include "core/renderer/renderer.hpp"

namespace fge {
  class FGE_API ImGuiLayer : public Layer {
  public:
    ImGuiLayer();

    // for some reason, clang is just broken and thinks
    // these functions are not implemented when they
    // very much are implemented
    bool onAppEvent(AppEvent& e) override;
    bool onRenderEvent(RenderEvent& e) override;
    bool onKeyboardEvent(KeyboardEvent& e) override;
    bool onMouseEvent(MouseEvent& e) override;
    
  private:
    App* app;
		bool blockInputEvents_{false};
    bool blockAppEvents_{false};
    //bool dockSpaceOpen_{true};
    bool vsyncEnabled_{false};

    u64 clickCount_{0};


    static void setDarkThemeColors();
  };
}