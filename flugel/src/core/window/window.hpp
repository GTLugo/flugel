#pragma once

#include "core/events/notifier.hpp"
#include "core/events/window_event.hpp"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

namespace Flugel {
  class FLUGEL_API Window {
    struct SDLWindowDelete {
      void operator()(SDL_Window* w) const {
        SDL_DestroyWindow(w);
      }
    };

  public:
    const std::string title{"SANDBOX"};
    const uint32_t width{800}, height{450};

    Notifier<WindowCloseEvent> closeNotifier{};
  public:
    Window();
    virtual ~Window();

    void processInput();
    void swapBuffer();

    const Unique<SDL_Window, SDLWindowDelete>& sdlWindow() const { return sdlWindow_; }
  private:
    Unique<SDL_Window, SDLWindowDelete> sdlWindow_{nullptr};
    Unique<SDL_GLContext> sdlGlContext_{nullptr};
  private:
    void init();
  };
}