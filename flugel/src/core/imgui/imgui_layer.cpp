#include "imgui_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"
#include "core/renderer/renderer.hpp"

#include <imgui.h>
// WINDOW API
#if defined(FLUGEL_USE_GLFW)
  #include <backends/imgui_impl_glfw.h>
  // RENDER API
  #if defined(FLUGEL_USE_OPENGL)
    #include <backends/imgui_impl_opengl3.h>
    #define IMGUI_RENDER_IMPL_INIT(glslVersion) ImGui_ImplOpenGL3_Init(glslVersion)
    #define IMGUI_WINDOW_IMPL_INIT(window, installCallbacks) ImGui_ImplGlfw_InitForOpenGL(window, installCallbacks)
    #define IMGUI_NEW_FRAME() ImGui_ImplOpenGL3_NewFrame(); ImGui_ImplGlfw_NewFrame()
  #endif
  #if defined(FLUGEL_USE_VULKAN)
    #include <backends/imgui_impl_vulkan.h>
  #endif
  #if defined(FLUGEL_USE_D3D11)
    #include <backends/imgui_impl_dx11.h>
  #endif
#endif
#if defined(FLUGEL_USE_SDL2)
#include <backends/imgui_impl_sdl.h>
#endif
#if defined(FLUGEL_USE_WIN32)
#include <backends/imgui_impl_win32.h>
#endif
  

namespace fge {
  ImGuiLayer::ImGuiLayer::ImGuiLayer() 
    : Layer{"imgui_layer"} {
    app = &App::instance();
  }

  bool ImGuiLayer::onAppEvent(AppEvent& e) {
    switch (e.action()) {
      case AppEvent::Start: {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();
        setDarkThemeColors();
		    auto* window = static_cast<GLFWwindow*>(app->window().nativeWindow());

        IMGUI_WINDOW_IMPL_INIT(window, true);
        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool ImGuiLayer::onRenderEvent(RenderEvent& e) {
    switch (e.action()) {
      case RenderEvent::Start: {
        IMGUI_RENDER_IMPL_INIT("#version 460");
        vsyncEnabled_ = app->window().isVSync();
        return false;
      }
      case RenderEvent::BeginFrame: {
        ImGuiIO& io{ImGui::GetIO()};
        io.DisplaySize = ImVec2(app->window().dims().x, app->window().dims().y);
        io.DeltaTime = Time::delta<Seconds>();
        //FGE_DEBUG("Time: {}", app.time().deltaTime<Seconds>());

        IMGUI_NEW_FRAME();
        ImGui::NewFrame();
        return false;
      }
      case RenderEvent::ImGuiStep: {
        ImGuiIO& io{ImGui::GetIO()};

        ImGuiDockNodeFlags dockspaceFlags =
            ImGuiDockNodeFlags_None /*|
            ImGuiDockNodeFlags_AutoHideTabBar*/;
        ImGuiWindowFlags dockspaceWindowFlags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        std::string title{"Flugel Engine | " + App::instance().window().title()};
        ImGui::Begin(title.c_str(), nullptr, dockspaceWindowFlags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        ImGuiID dockspaceId{ImGui::GetID("Engine Dock Space")};
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

        if (ImGui::BeginMenuBar()) {
          if (ImGui::BeginMenu("Menu")) {
            ImGui::MenuItem("Vsync", nullptr, &vsyncEnabled_);
            app->window().setVSync(vsyncEnabled_);
            ImGui::EndMenu();
          }
          ImGui::EndMenuBar();
        } ImGui::End();

        ImGui::Begin("App", nullptr, ImGuiWindowFlags_NoScrollbar); { // https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window
          ImVec2 winSize{ImGui::GetWindowSize()};

          // TODO: Fix aspect ratio
//          appWinSize = vec2{winSize.x, winSize.y};
//
//
//          if (data->DesiredSize.x >= appWinSize_.x && data->DesiredSize.y >= appWinSize_.y) {
//            float widthRatio{appWinSize_.x / data->CurrentSize.x};
//            float heightRatio{appWinSize_.y / data->CurrentSize.y};
//            if (widthRatio >= heightRatio) {
//              data->DesiredSize.x = appImageSize_.x = data->CurrentSize.x * aspectRatio_;
//              data->DesiredSize.y = appImageSize_.y = appWinSize_.y;
//            } else {
//              data->DesiredSize.x = appImageSize_.x = appWinSize_.x;
//              data->DesiredSize.y = appImageSize_.y = data->CurrentSize.y / aspectRatio_;
//            }
//          } else if (data->DesiredSize.x >= appWinSize_.x) {
//            data->DesiredSize.x = appImageSize_.x = data->CurrentSize.x * aspectRatio_;
//            data->DesiredSize.y = appImageSize_.y = appWinSize_.y;
//          } else {
//            data->DesiredSize.x = appImageSize_.x = appWinSize_.x;
//            data->DesiredSize.y = appImageSize_.y = data->CurrentSize.y / aspectRatio_;
//          }
//          ImGui::SetNextWindowSize()
//          ImGui::SetNextWindowSizeConstraints(
//              ImVec2(0, 0),
//              ImVec2(FLT_MIN, FLT_MAX),
//              ImGuiLayer::keepAspect);
          ImGui::BeginChild("GameRender");
          ImVec2 winSizeNew{ImGui::GetWindowSize()};
          if (Shared<FrameBuffer> fb = Renderer::defaultFrameBuffer().lock()) {
            ImGui::Image(
                (ImTextureID)reinterpret_cast<u32>(fb->textureBuffer()->handle()),
                winSizeNew, //{appImageSize_.x, appImageSize_.y},
                ImVec2{0, 1},
                ImVec2{1, 0});
          }
          ImGui::EndChild();
        } ImGui::End();

        ImGui::Begin("Log");
        ImGui::Text("UwU I'm a log OwO");
        ImGui::End();

        ImGui::Begin("Engine Stats");
        ImGui::Text("FPS: %i", static_cast<int>(floor(io.Framerate)));
        ImGui::Text("FT: %.3f ms", 1000. / io.Framerate);
        ImGui::End();

        ImGui::Begin("App Stats");
        ImGui::Text("Click Count: %llu", clickCount_);
        ImGui::End();
        return false;
      }
      case RenderEvent::EndFrame: {
        ImGuiIO& io{ImGui::GetIO()};
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
          // Update and Render additional Platform Windows
          // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
          //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
          ImGui::UpdatePlatformWindows();
          ImGui::RenderPlatformWindowsDefault();
          App::instance().window().context().setCurrent(true);
        }
        return false;
      }
      case RenderEvent::Stop: {
		    ImGui_ImplOpenGL3_Shutdown();
		    ImGui_ImplGlfw_Shutdown();
		    ImGui::DestroyContext();
        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool ImGuiLayer::onKeyboardEvent(KeyboardEvent& e) {
    if (blockInputEvents_) {
      ImGuiIO& io = ImGui::GetIO();
      return io.WantCaptureKeyboard;
    }
    return false;
  }

  bool ImGuiLayer::onMouseEvent(MouseEvent& e) {
    if (e.check<Mouse::Left>(Mouse::Pressed)) {
      ++clickCount_;
    }

    if (blockInputEvents_) {
      ImGuiIO& io = ImGui::GetIO();
      return io.WantCaptureMouse;
    }
    return false;
  }

  void ImGuiLayer::keepAspect(ImGuiSizeCallbackData* data) {
    // Find minimum size that keeps aspect ratio
    float startRatio{data->CurrentSize.x / data->CurrentSize.y};
    FGE_DEBUG_ENG("WIN width: {} height: {}", appWinSize_.x, appWinSize_.y);
    FGE_DEBUG_ENG("START width: {} height: {} ratio: {}", data->CurrentSize.x, data->CurrentSize.y, startRatio);

    if (data->DesiredSize.x >= appWinSize_.x && data->DesiredSize.y >= appWinSize_.y) {
      float widthRatio{appWinSize_.x / data->CurrentSize.x};
      float heightRatio{appWinSize_.y / data->CurrentSize.y};
      if (widthRatio >= heightRatio) {
        data->DesiredSize.x = appImageSize_.x = data->CurrentSize.x * aspectRatio_;
        data->DesiredSize.y = appImageSize_.y = appWinSize_.y;
      } else {
        data->DesiredSize.x = appImageSize_.x = appWinSize_.x;
        data->DesiredSize.y = appImageSize_.y = data->CurrentSize.y / aspectRatio_;
      }
    } else if (data->DesiredSize.x >= appWinSize_.x) {
      data->DesiredSize.x = appImageSize_.x = data->CurrentSize.x * aspectRatio_;
      data->DesiredSize.y = appImageSize_.y = appWinSize_.y;
    } else {
      data->DesiredSize.x = appImageSize_.x = appWinSize_.x;
      data->DesiredSize.y = appImageSize_.y = data->CurrentSize.y / aspectRatio_;
    }

    float endRatio{data->DesiredSize.x / data->DesiredSize.y};
    FGE_DEBUG_ENG("END width: {} height: {} ratio: {}", data->DesiredSize.x, data->DesiredSize.y, endRatio);
  }

	void ImGuiLayer::setDarkThemeColors() {
		auto& colors = ImGui::GetStyle().Colors;

    auto dark0{ImVec4{ 0.03f, 0.03f, 0.03f, 1.0f }};
    auto dark1{ImVec4{ 0.05f, 0.05f, 0.05f, 1.0f }};
    auto dark2{ImVec4{ 0.05f, 0.05f, 0.05f, 1.0f }};

		colors[ImGuiCol_WindowBg] = dark0;

		// Headers
		colors[ImGuiCol_Header]        = dark1;
		colors[ImGuiCol_HeaderHovered] = dark1;
		colors[ImGuiCol_HeaderActive]  = dark1;
		
		// Buttons
		colors[ImGuiCol_Button]        = dark1;
		colors[ImGuiCol_ButtonHovered] = dark1;
		colors[ImGuiCol_ButtonActive]  = dark1;

		// Frame BG
		colors[ImGuiCol_FrameBg]        = dark1;
		colors[ImGuiCol_FrameBgHovered] = dark1;
		colors[ImGuiCol_FrameBgActive]  = dark1;

		// Tabs
		colors[ImGuiCol_Tab]                = dark1;
		colors[ImGuiCol_TabHovered]         = dark1;
		colors[ImGuiCol_TabActive]          = dark1;
		colors[ImGuiCol_TabUnfocused]       = dark1;
		colors[ImGuiCol_TabUnfocusedActive] = dark1;

		// Title
		colors[ImGuiCol_TitleBg]          = dark1;
		colors[ImGuiCol_TitleBgActive]    = dark1;
		colors[ImGuiCol_TitleBgCollapsed] = dark1;
	}
}