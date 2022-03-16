#pragma once

#include "core/layers/layer.hpp"
#include "core/renderer/renderer.hpp"

#include <imgui.h>

namespace ff {
  class ImGuiLayer : public Layer {
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
    bool enforceAspectRatio_{false};
    // these should probably be moved sometime
    static inline float aspectRatio_{16.f / 9.f};
    static inline vec2 appWinSize_{0,0};
    static inline vec2 appImageSize_{0,0};

    ImGuiDockNodeFlags dockspaceFlags_ =
        ImGuiDockNodeFlags_None /*|
        ImGuiDockNodeFlags_AutoHideTabBar*/;
    ImGuiWindowFlags dockspaceWindowFlags_ =
        //ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;
    ImGuiWindowFlags mainAppWindowFlags_ =
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar;

    static void setDarkThemeColors();
    static void keepAspect(ImGuiSizeCallbackData* data);

    static void rendererInit();
    static void windowInit();
    static void newFrame();
    static void renderDrawData();
    static void shutdownRenderer();
    static void shutdownWindow();
  };
}