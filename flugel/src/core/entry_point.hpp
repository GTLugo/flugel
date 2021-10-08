#pragma once

#include "core/app.hpp"

int32_t main(int32_t argCount = 0, char* args[] = nullptr) {
  Flugel::Log::init();

  Flugel::Unique<Flugel::App> app{Flugel::createApp()};
  app->run();

  return EXIT_SUCCESS;
}

#if defined(_WIN32) && defined(NDEBUG)
  int32_t WINAPI WinMain(
      HINSTANCE h_instance,
      HINSTANCE h_prev_instance, 
      LPSTR lp_cmd_line,
      int32_t n_cmd_show) {
    return main();
  }
#endif