#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#ifdef defined(_WIN32) && (defined(RELEASE) || defined(MINREL))
#include <windows.h>
#endif

#include "app.hpp"

extern Flugel::App* Flugel::CreateApp();

int run(int argc = 0, char* argv[] = nullptr) {
  Flugel::App* app = nullptr;
  try {
    app = Flugel::CreateApp();
    app->run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    if (app != nullptr) delete app;
    return EXIT_FAILURE;
  }
  
  if (app != nullptr) delete app;
  return EXIT_SUCCESS;
}

#ifdef _WIN32
  #if defined(RELEASE) || defined(MINREL)
    int WINAPI WinMain(
        HINSTANCE h_instance, 
        HINSTANCE h_prev_instance, 
        LPSTR lp_cmd_line, 
        int n_cmd_show) {
      return run();
    }
  #elif defined(DEBUG) || defined(RELDEB)
    int main(int argc, char* argv[]) {
      return run(argc, argv);
    }
  #endif
#else
  int main(int argc, char* argv[]) {
    return run(argc, argv);
  }
#endif