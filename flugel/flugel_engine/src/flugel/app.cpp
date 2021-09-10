#include "app.hpp"

#include "logging/log.hpp"

#include <iostream>

namespace Flugel {
  App::App() {

  }

  App::~App() {

  }

  void App::run() {
    int x = 0;
    while (x < 1000) {
      // std::cout << "Running!\n";
      FLUGEL_DEBUG("Running...");
      ++x;
    }
    FLUGEL_DEBUG("Finished running!");
  }
}