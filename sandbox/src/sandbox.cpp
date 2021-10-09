#include "test_layer.hpp"

#include "flugel.hpp"

namespace Sandbox {
  class App : public Flugel::App {
    public:
      App()
        : Flugel::App{Flugel::WindowProperties{
          "SANDBOX", // title
          800, // width
          450, // height
          false, // vsync
          false, // fullscreen
          false, // borderless
          false // custom window decorations
        }} {
        pushLayer(new TestLayer{time()});
      }

      virtual ~App() override {
        FLUGEL_TRACE("Destructing sandbox...");
      };
  };
}

namespace Flugel {
  Unique<App> createApp() {
    return std::move(makeUnique<Sandbox::App>());
  }
}