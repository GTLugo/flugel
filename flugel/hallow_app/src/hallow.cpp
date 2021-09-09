#include "flugel.hpp"

class HallowApp : public Flugel::App {
  public:
    HallowApp() {}
    ~HallowApp() {}
  private:
};

Flugel::App* Flugel::CreateApp() {
  return new HallowApp{};
}