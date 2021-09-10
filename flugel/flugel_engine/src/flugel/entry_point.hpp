#pragma once

// #include <cstdlib>
// #include <iostream>
// #include <stdexcept>
#if defined(_WIN32) && defined(NDEBUG)
#include <windows.h>
#endif

#include "app.hpp"
#include "logging/log.hpp"

extern Flugel::App* Flugel::CreateApp();

int run(int argc = 0, char* argv[] = nullptr) {
  Flugel::Log::init();

  Flugel::App* app = Flugel::CreateApp();
  app->run();
  delete app;

  return EXIT_SUCCESS;
}

#ifdef _WIN32
  #ifdef NDEBUG
    int WINAPI WinMain(
        HINSTANCE h_instance, 
        HINSTANCE h_prev_instance, 
        LPSTR lp_cmd_line, 
        int n_cmd_show) {
      return run();
    }
  #else
    int main(int argc, char* argv[]) {
      return run(argc, argv);
    }
  #endif
#else
  int main(int argc, char* argv[]) {
    return run(argc, argv);
  }
#endif