#include "flugel.hpp"

class SandboxApp : public Flugel::App {
  public:
    SandboxApp(const Flugel::WindowProps& props = {})
      : App{props} {}
    ~SandboxApp() {}
};

Flugel::App* Flugel::CreateApp() {
  Flugel::WindowProps props{
    "SANDBOX",
    800,
    450,
    false
  };
  return new SandboxApp{props};
}