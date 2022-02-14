#include "imgui_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

//#include <glad/gl.h>
//#include <GLFW/glfw3.h>
#include <imgui.h>
// RENDER API
#if defined(FLUGEL_USE_OPENGL)
  #include <backends/imgui_impl_opengl3.h>
#endif
#if defined(FLUGEL_USE_VULKAN)
  #include <backends/imgui_impl_vulkan.h>
#endif
#if defined(FLUGEL_USE_D3D11)
  #include <backends/imgui_impl_dx11.h>
#endif
// WINDOW API
#if defined(FLUGEL_USE_GLFW)
  #include <backends/imgui_impl_glfw.h>
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
    
  }

  bool ImGuiLayer::onAppEvent(AppEvent& e) {
    switch (e.type()) {
      case AppEventType::Start: {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
        // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();
        setDarkThemeColors();
        App& app = App::instance();
		    auto* window = static_cast<GLFWwindow*>(app.window().nativeWindow());
        
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        return false;
      }
      default: {
        return false;
      }
    }
  }

  bool ImGuiLayer::onRenderEvent(RenderEvent& e) {
    switch (e.type()) {
      case RenderEventType::Start: {
        ImGui_ImplOpenGL3_Init("#version 460");
        return false;
      }
      case RenderEventType::BeginImGui: {
        App& app = App::instance();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.DisplaySize = ImVec2(app.window().dims().x, app.window().dims().y);
        io.DeltaTime = fge::App::time().delta<Seconds>();
        //FGE_DEBUG("Time: {}", app.time().deltaTime<Seconds>());

        ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("App Stats");
        ImGui::Text("FPS: %.1f (%.3f ms)", io.Framerate, 1000. / io.Framerate);
        ImGui::End();
        
        return false;
      }
      case RenderEventType::EndImGui: {
        ImGui::Render();
        std::string a{"0"};
        auto b = *(a.end() - 1);
        return false;
      }
      case RenderEventType::EndFrame: {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return false;
      }
      case RenderEventType::Stop: {
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
    if (blockInputEvents_) {
			ImGuiIO& io = ImGui::GetIO();
      return io.WantCaptureMouse;
    }
    return false;
  }

	void ImGuiLayer::setDarkThemeColors() {
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}