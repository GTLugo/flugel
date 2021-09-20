#include "flugel.hpp"

class SandboxApp : public Flugel::App {
  public:
    SandboxApp(const Flugel::WindowProps& props = {})
      : App{props} {}
    ~SandboxApp() {}
  private:
};

Flugel::App* Flugel::CreateApp() {
  Flugel::WindowProps props{
    "ALPHA",
    800,
    450,
    false
  };
  return new SandboxApp{props};
}