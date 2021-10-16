#pragma once

#include "core/app.hpp"

int32_t main(int32_t argCount = 0, char* args[] = nullptr) {
  fge::Log::init();

  fge::Unique<fge::App> app{fge::createApp()};
  try {
    app->run();
  } catch(const std::exception& e) {
    FGE_ERROR("EXCEPTION CAUGHT: {}", e.what());
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}

#if defined(_WIN32) && defined(NDEBUG)
  int32_t WINAPI WinMain(
      HINSTANCE h_instance,
      HINSTANCE h_prev_instance, 
      LPSTR lp_cmd_line,
      int32_t n_cmd_show) {
    return main(__argc, __argv);
  }
#endif