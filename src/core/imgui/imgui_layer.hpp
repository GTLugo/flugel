#pragma once

#include "core/layers/layer.hpp"
#include "core/renderer/renderer.hpp"
#include "core/app.hpp"

#include <imgui.h>

namespace ff {
  class ImGuiLayer final : public Layer {
  public:
    ImGuiLayer();

    bool onGameEvent(const GameEvent& e) final;
    bool onInputEvent(const InputEvent& e) final;
    
  private:
    App* app;
		bool blockInputEvents_{false};
    bool showStats_{false};
    bool vsyncEnabled_{false};
    bool enforceAspectRatio_{false};
    // these should probably be moved sometime
    static inline float aspectRatio_{16.f / 9.f};
    static inline vec2 appWinSize_{0, 0};
    static inline vec2 appImageSize_{0, 0};

    ImGuiDockNodeFlags dockspaceFlags_ =
        ImGuiDockNodeFlags_None;
    ImGuiWindowFlags dockspaceWindowFlags_ =
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