#include "flugel.hpp"

class Hallow : public Flugel::App {
  public:
    Hallow() {}
    ~Hallow() {}
  private:
};

Flugel::App* Flugel::CreateApp() {
  return new Hallow{};
}