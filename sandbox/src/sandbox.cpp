#include "flugel.hpp"

class SandboxApp : public Flugel::App {
  public:
    SandboxApp(const Flugel::WindowProps& props = {})
      : App{props} {}
    ~SandboxApp() {}

  private:
    virtual bool onStart(Flugel::AppStartEvent& e) override {
      return true;
    }
};

Flugel::App* Flugel::CreateApp() {
  Flugel::WindowProps props{
    "SANDBOX | Flugel",
    800,
    450,
    false
  };
  return new SandboxApp{props};
}