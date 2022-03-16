#pragma once

#include "core/app.hpp"

int main(int argCount = 0, char* args[] = nullptr) {
  ff::Log::init();

  ff::Unique<ff::App> app{ff::createApp()};
  try {
    app->run();
  } catch(const std::exception& e) {
    ff::Log::error("EXCEPTION CAUGHT: {}", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

#if defined(_WIN32) and defined(NDEBUG)
ff::i32 WINAPI WinMain(HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        ff::i32 nCmdShow) {
  return main(__argc, __argv);
}
#endif