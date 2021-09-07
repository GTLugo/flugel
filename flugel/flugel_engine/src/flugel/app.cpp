#include "app.hpp"

#include <iostream>

#include "log.hpp"

namespace Flugel {
  App::App() {

  }

  App::~App() {

  }

  void App::run() {
    while (true) {
      // std::cout << "Running!\n";
      FGL_DEBUG("Running!");
    }
  }
}