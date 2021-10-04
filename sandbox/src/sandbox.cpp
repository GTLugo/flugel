#include <flugel.hpp>

class SandboxApp : public Flugel::App {
  public:
    SandboxApp() = default;
    virtual ~SandboxApp() override = default;
};

Flugel::Unique<Flugel::App> Flugel::createApp() {
  return Flugel::makeUnique<SandboxApp>();
}