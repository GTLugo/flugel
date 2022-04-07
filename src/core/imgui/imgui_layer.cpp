#include "imgui_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"
#include "core/renderer/renderer.hpp"

#include <imgui.h>
#include <imgui_internal.h>

// TODO: Swap all of this for switch cases
#include <backends/imgui_impl_glfw.h>
// RENDER API
#ifdef FLUGEL_USE_OPENGL
  #include <backends/imgui_impl_opengl3.h>
#endif
#ifdef FLUGEL_USE_VULKAN
  #include <backends/imgui_impl_vulkan.h>
#endif
#ifdef FLUGEL_USE_D3D11
  #include <backends/imgui_impl_dx11.h>
#endif
  

namespace ff {
  ImGuiLayer::ImGuiLayer::ImGuiLayer() 
    : Layer{"imgui_layer"} {
    app = &App::instance();
  }

  bool ImGuiLayer::onGameEvent(const GameEvent& e) {
    return std::visit(EventVisitor{
        [=](const GameStartEvent&) {
          vsyncEnabled_ = app->window().isVSync();
          IMGUI_CHECKVERSION();
          ImGui::CreateContext();
          ImGuiIO& io = ImGui::GetIO();
          io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
          io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
          io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
          //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

          ImGui::StyleColorsDark();
          setDarkThemeColors();

          windowInit();
          rendererInit();
          return false;
        },
        [=](const GameBeginFrameEvent&) {
          ImGuiIO& io{ImGui::GetIO()};
          io.DisplaySize = ImVec2(static_cast<float>(app->window().dims().x), static_cast<float>(app->window().dims().y));
          io.DeltaTime = static_cast<float>(Time::delta<Seconds>());

          newFrame();
          return false;
        },
        [=](const GameImGuiEvent&) {
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
          windowClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoDockingOverMe;
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
                  reinterpret_cast<ImTextureID*>(static_cast<u64>(fb->textureBuffer()->handle())),
                  {appImageSize_.x, appImageSize_.y},
                  ImVec2{0, 1},
                  ImVec2{1, 0});
            }
          } ImGui::EndChild();
        } ImGui::End();

          // Stats overlay
          if (showStats_) {
            ImGui::Begin("Engine Stats");
            ImGui::Checkbox("Vsync", &vsyncEnabled_);
            app->window().setVSync(vsyncEnabled_);
            ImGui::SameLine();
            ImGui::Text("| FPS: %i", static_cast<int>(floor(io.Framerate)));
            ImGui::Text("Frametime: %.3f ms", 1000. / io.Framerate);
            ImGui::End();
          }

          return false;
        },
        [](const GameEndFrameEvent&) {
          ImGuiIO& io{ImGui::GetIO()};
          ImGui::Render();
          renderDrawData();
          if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            // Update and Render additional Platform Windows
            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
            //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            App::instance().window().context().setCurrent(true);
          }
          return false;
        },
        [](const GameStopEvent&) {
          shutdownRenderer();
          shutdownWindow();
          ImGui::DestroyContext();
          return false;
        },
        [](const auto& event) { return false; }
    }, e);
  }

  bool ImGuiLayer::onInputEvent(const InputEvent& e) {
    return std::visit(EventVisitor{
      [=](const InputKeyEvent& event) {
        if (event.test<Key::Accent>(Key::Pressed) && event.test<Modifier::Control>(Key::Pressed)) {
          showStats_ = !showStats_;
          Log::debug_e("Show Stats: {}", showStats_);
        }

        if (blockInputEvents_) {
          ImGuiIO& io = ImGui::GetIO();
          return io.WantCaptureKeyboard;
        }
        return false;
      },
      [=](const InputMouseEvent& event) {
        if (blockInputEvents_) {
          ImGuiIO& io = ImGui::GetIO();
          return io.WantCaptureMouse;
        }
        return false;
      },
      [](const auto& event) { return false; }
    }, e);
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

  void ImGuiLayer::rendererInit() {
    auto* window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        ImGui_ImplOpenGL3_Init("#version 460");
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
  }

  void ImGuiLayer::windowInit() {
    auto* window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
  }

  void ImGuiLayer::newFrame() {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        ImGui_ImplOpenGL3_NewFrame();
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void ImGuiLayer::renderDrawData() {
    auto* window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
  }

  void ImGuiLayer::shutdownRenderer() {
    auto* window = static_cast<GLFWwindow*>(App::instance().window().nativeWindow());
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        ImGui_ImplOpenGL3_Shutdown();
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
  }

  void ImGuiLayer::shutdownWindow() {
    ImGui_ImplGlfw_Shutdown();
  }
}