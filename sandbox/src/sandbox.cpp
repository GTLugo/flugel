#include "test_layer.hpp"

#include "flugel.hpp"

namespace sbx {
  class Sandbox : public fge::App {
    public:
      Sandbox()
        : fge::App{{
          "SANDBOX", // title
          800, // width
          450, // height
          fge::Renderer::OpenGL,
          false, // vsync
          false, // fullscreen
          false, // borderless
          true // custom window decorations
        }} {
        FGE_TRACE("Constructing sandbox...");

        
        pushLayer(new TestLayer{});
        pushOverlay(new fge::ImGuiLayer());
      }

      virtual ~Sandbox() override {
        FGE_TRACE("Destructing sandbox...");
      };
  };
}

namespace fge {
  Unique<App> createApp() {
    return std::move(makeUnique<sbx::Sandbox>());
  }
}