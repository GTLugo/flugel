#pragma once

#include "core/layers/layer.hpp"

namespace fge {
  class ImGuiLayer : public Layer {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual bool onAppEvent(AppEvent& e) override;
    virtual bool onRenderEvent(RenderEvent& e) override;
    virtual bool onKeyboardEvent(KeyboardEvent& e) override;
    virtual bool onMouseEvent(MouseEvent& e) override;
    
  private:
		bool blockEvents_{true};

    static void setDarkThemeColors();
  };
}