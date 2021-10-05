#pragma once

#include "core/app.hpp"

int main(int argCount = 0, char* args[] = nullptr) {
  Flugel::Log::init();

  Flugel::Unique<Flugel::App> app{Flugel::createApp()};
  FLUGEL_TRACE_E("Running app...");
  app->run();
  FLUGEL_TRACE_E("App finished running!");

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