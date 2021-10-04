#include "window.hpp"

namespace Flugel {
  Window::Window() {
    init();
  }

  Window::~Window() {
    
  }

  void Window::init() {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      FLUGEL_CRIT_E("SDL ERROR: Failed to initialize SDL! {0}", SDL_GetError());
    }

    uint32_t WindowFlags{SDL_WINDOW_OPENGL};
    sdlWindow_ = Unique<SDL_Window, SDLWindowDelete>(
      SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        WindowFlags
      )
    );

    if (sdlWindow_ == nullptr) {
      FLUGEL_CRIT_E("SDL ERROR: Failed to create window! {0}", SDL_GetError());
    }

    sdlGlContext_ = makeUnique<SDL_GLContext>(
      SDL_GL_CreateContext(sdlWindow_.get())
    );
  }

  void Window::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      // FLUGEL_TRACE_E("EVENT!");
      switch (event.type) {
        case SDL_KEYDOWN: {
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: {
              WindowCloseEvent e{};
              closeNotifier.notify(e);
            }
            default: {
              break;
            }
          }
        }
        case SDL_QUIT: {
          WindowCloseEvent e{};
          closeNotifier.notify(e);
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void Window::swapBuffer() {
    SDL_GL_SwapWindow(sdlWindow_.get());
  }
}