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

int main(int argc = 0, char* argv[] = nullptr) {
  Flugel::Log::init();
  
  Flugel::App* app = Flugel::CreateApp();
  app->run();
  delete app;

  return EXIT_SUCCESS;
}

#if defined(_WIN32) && defined(NDEBUG)
  int WINAPI WinMain(
      HINSTANCE h_instance, 
      HINSTANCE h_prev_instance, 
      LPSTR lp_cmd_line, 
      int n_cmd_show) {
    return main();
  }
#endif