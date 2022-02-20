#include "flugel.hpp"
#include "entry_point.hpp"

#include "test_layer.hpp"

namespace sbx {
  class Sandbox : public fge::App {
    public:
      Sandbox()
        : fge::App{{
          .title       = "SANDBOX", // title
          .width       = 800, // width
          .height      = 450, // height
          .renderApi   = fge::Renderer::API::OpenGL
        }} {
        FGE_TRACE("Constructing sandbox...");
        //toggleImGui(false);
        pushLayer(new TestLayer{});
      }

      ~Sandbox() override {
        FGE_TRACE("Destructing sandbox...");
      };
  };
}

namespace fge {
  Unique<App> createApp() {
    return std::move(makeUnique<sbx::Sandbox>());
  }
}