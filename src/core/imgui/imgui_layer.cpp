#include "imgui_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"
#include "core/renderer/renderer.hpp"

#include <imgui.h>
#include <imgui_internal.h>

// TODO: Swap all of this for switch cases
// WINDOW API
#if defined(FLUGEL_USE_GLFW)
  #include <backends/imgui_impl_glfw.h>
  #define IMGUI_SHUTDOWN_WINDOW() ImGui_ImplGlfw_Shutdown()
  // RENDER API
  #if defined(FLUGEL_USE_OPENGL)
    #include <backends/imgui_impl_opengl3.h>
    #define IMGUI_RENDER_IMPL_INIT(glslVersion) ImGui_ImplOpenGL3_Init(glslVersion)
    #define IMGUI_WINDOW_IMPL_INIT(window, installCallbacks) ImGui_ImplGlfw_InitForOpenGL(window, installCallbacks)
    #define IMGUI_NEW_FRAME() ImGui_ImplOpenGL3_NewFrame(); ImGui_ImplGlfw_NewFrame()
    #define IMGUI_RENDER_DRAW_DATA(draw_data) ImGui_ImplOpenGL3_RenderDrawData(draw_data)
    #define IMGUI_SHUTDOWN_RENDERER() ImGui_ImplOpenGL3_Shutdown()
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
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        // Main docking zone
        std::string title{"Flugel Engine | " + App::instance().window().title()};
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
        ImGui::Begin(title.c_str(), nullptr, dockspaceWindowFlags_); ImGui::PopStyleVar(2); {
          ImGuiID dockspaceId{ImGui::GetID("Engine Dock Space")};
          ImGui::DockSpace(dockspaceId, {0.0f, 0.0f}, dockspaceFlags_);

          static bool virgin{true};
          if (virgin) { // go gently
            ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
            ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags_ | ImGuiDockNodeFlags_DockSpace);
            //ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

            ImGui::DockBuilderDockWindow("MainApp", dockspaceId);
            ImGui::DockBuilderFinish(dockspaceId);

            virgin = false;
          } else; // go harder
        } ImGui::End();

        // Main app window
        // https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
        ImGuiWindowClass windowClass;
        //windowClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
        ImGui::SetNextWindowClass(&windowClass);
        ImGui::Begin("MainApp", nullptr, mainAppWindowFlags_); ImGui::PopStyleVar(3); {
          ImVec2 winPos{ImGui::GetWindowPos()};
          ImVec2 winSize{ImGui::GetWindowSize()};
          appWinSize_ = vec2{winSize.x, winSize.y};
          if (enforceAspectRatio_) {
            ImGui::SetNextWindowSizeConstraints(
                {0, 0},
                {FLT_MIN, FLT_MAX},
                ImGuiLayer::keepAspect);
            float magicVerticalPaddingNumberIHaveNoIdeaWhyExists{10};
            ImGui::SetNextWindowPos({
                winPos.x + (appWinSize_.x / 2.f) - (appImageSize_.x / 2.f),
                winPos.y + (appWinSize_.y / 2.f) - (appImageSize_.y / 2.f) //+ magicVerticalPaddingNumberIHaveNoIdeaWhyExists
            });
          } else {
            appImageSize_ = appWinSize_;
          }
          ImGui::BeginChild("GameRender", {}, false, mainAppWindowFlags_); {
            if (Shared<FrameBuffer> fb = Renderer::defaultFrameBuffer().lock()) {
              ImGui::Image(
                  (ImTextureID)reinterpret_cast<u32>(fb->textureBuffer()->handle()),
                  {appImageSize_.x, appImageSize_.y},
                  ImVec2{0, 1},
                  ImVec2{1, 0});
            }
          } ImGui::EndChild();
        } ImGui::End();

        // Stats overlay
        ImGui::Begin("Engine Stats"); {
          ImGui::Checkbox("Vsync", &vsyncEnabled_);
          app->window().setVSync(vsyncEnabled_);
          ImGui::SameLine();
          ImGui::Text("| FPS: %i", static_cast<int>(floor(io.Framerate)));
          ImGui::Text("Frametime: %.3f ms", 1000. / io.Framerate);
        } ImGui::End();

        return false;
      }
      case RenderEvent::EndFrame: {
        ImGuiIO& io{ImGui::GetIO()};
        ImGui::Render();
        IMGUI_RENDER_DRAW_DATA(ImGui::GetDrawData());
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
        IMGUI_SHUTDOWN_RENDERER();
        IMGUI_SHUTDOWN_WINDOW();
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
    if (blockInputEvents_) {
      ImGuiIO& io = ImGui::GetIO();
      return io.WantCaptureMouse;
    }
    return false;
  }

  void ImGuiLayer::keepAspect(ImGuiSizeCallbackData* data) {
    // Find minimum size that keeps aspect ratio
    data->DesiredSize.x = appImageSize_.x = data->CurrentSize.y * aspectRatio_;
    data->DesiredSize.y = appImageSize_.y = data->CurrentSize.y;
    float widthRatio{data->DesiredSize.x / appWinSize_.x};
    if (widthRatio > 1) {
      data->DesiredSize.x = appImageSize_.x /= widthRatio;
      data->DesiredSize.y = appImageSize_.y /= widthRatio;
    }
  }

	void ImGuiLayer::setDarkThemeColors() {
		auto& colors = ImGui::GetStyle().Colors;
    auto& style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;

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