#include <flugel.hpp>

namespace Sandbox {
  class App : public Flugel::App {
    public:
      App()
        : Flugel::App{Flugel::WindowProperties{
          "SANDBOX",
          800,
          450,
          false
        }} {}
      virtual ~App() override = default;
  };
}

namespace Flugel {
  Unique<App> createApp() {
    return makeUnique<Sandbox::App>();
  }
}