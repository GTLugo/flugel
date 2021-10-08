#include "sandbox_layer.hpp"

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
        pushLayer(new SandboxLayer{&time()});
      }

      virtual ~App() override = default;
  };
}

namespace Flugel {
  Unique<App> createApp() {
    return makeUnique<Sandbox::App>();
  }
}