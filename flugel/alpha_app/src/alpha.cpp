#include "flugel.hpp"

class AlphaApp : public Flugel::App {
  public:
    AlphaApp(const Flugel::WindowProps& props = {})
      : App{props} {}
    ~AlphaApp() {}
  private:
};

Flugel::App* Flugel::CreateApp() {
  Flugel::WindowProps props{
    "ALPHA",
    800,
    450,
    false
  };
  return new AlphaApp{props};
}