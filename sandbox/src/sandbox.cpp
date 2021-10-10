#include "test_layer.hpp"

#include "flugel.hpp"

namespace Sandbox {
  class App : public fge::App {
    public:
      App()
        : fge::App{fge::WindowProperties{
          "SANDBOX", // title
          800, // width
          450, // height
          false, // vsync
          false, // fullscreen
          false, // borderless
          false // custom window decorations
        }} {
        pushLayer(new TestLayer{});
      }

      virtual ~App() override {
        FGE_TRACE("Destructing sandbox...");
      };
  };
}

namespace fge {
  Unique<App> createApp() {
    return std::move(makeUnique<Sandbox::App>());
  }
}