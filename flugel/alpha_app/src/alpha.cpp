#include "flugel.hpp"

class AlphaApp : public Flugel::App {
  public:
    AlphaApp() {}
    ~AlphaApp() {}
  private:
};

Flugel::App* Flugel::CreateApp() {
  double* nums = new double[5];
  delete[] nums;
  uint32_t * count = new uint32_t{1};
  delete count;
  return new AlphaApp{};
}