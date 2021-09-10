#include "flugel.hpp"

class AlphaApp : public Flugel::App {
  public:
    AlphaApp() {}
    ~AlphaApp() {}
  private:
};

Flugel::App* Flugel::CreateApp() {
  return new AlphaApp{};
}