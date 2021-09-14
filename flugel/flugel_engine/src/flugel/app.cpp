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
      FLUGEL_DEBUG_ENGINE("Running...");
      // ++x;
    }
    FLUGEL_DEBUG_ENGINE("Finished running!");

    // #ifndef NDEBUG
    // FLUGEL_INFO_ENGINE("Press ENTER to continue...");
    // std::cin.get();
    // #endif
  }
}