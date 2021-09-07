#include "flugel.hpp"

int main(int argc, char* argv[]) {
  Flugel::App* app = new Flugel::App();
  app->run();
  delete app;
}