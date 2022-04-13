#pragma once

#include "core/app.hpp"

int main(int argCount = 0, char* args[] = nullptr) {
  ff::Log::init();
  try {
    ff::Unique<ff::App> app{ff::createApp()};
    app->run();
  } catch(const std::exception& e) {
    ff::Log::critical_e(e.what());
    return EXIT_FAILURE;
  }
  ff::Log::trace_e("Engine stopped successfully.");
}

#if defined(_WIN32) and defined(NDEBUG)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  return main(__argc, __argv);
}
#endif