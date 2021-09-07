#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#if defined(_WIN32) && (defined(RELEASE) || defined(MINREL))
#include <windows.h>
#endif

#include "app.hpp"
#include "log.hpp"

extern Flugel::App* Flugel::CreateApp();

int run(int argc = 0, char* argv[] = nullptr) {
  Flugel::Log::init();
  FGL_ENGINE_INFO("Initialized engine logger!");
  FGL_INFO("Initialized app logger!");

  // FGL_ENGINE_DEBUG("debug log test!");
  // FGL_ENGINE_CRIT("critical error log test!");
  // FGL_WARN("warn log test!");
  // FGL_ERROR("error log test!");
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