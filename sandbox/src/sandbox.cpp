#include <flugel.hpp>

class SandboxApp : public Flugel::App {
  public:
    SandboxApp()
      : Flugel::App{Flugel::WindowProperties{
        "SANDBOX",
        800,
        450,
        false
      }} {}
    virtual ~SandboxApp() override = default;
};

Flugel::Unique<Flugel::App> Flugel::createApp() {
  return Flugel::makeUnique<SandboxApp>();
}