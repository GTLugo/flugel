// https://bcmpinc.wordpress.com/2015/08/18/creating-an-opengl-4-5-context-using-sdl2-and-glad/
#include "sdl2_window.hpp"

#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/input/input.hpp"

#include <glad/glad.h>

namespace fge {
  static uint8_t sdl2WindowCount_s{0};

  static void sdl2ErrorCallback(const char* message) {
    FGE_ERROR_ENG("SDL Error {} | {}", SDL_GetError(), message);
  }

  Sdl2Window::Sdl2Window(const WindowProperties& props)
    : Window{props} {
    init();
  }

  Sdl2Window::~Sdl2Window() {
    FGE_TRACE_ENG("Destructing Sdl2Window...");
    shutdown();
  }

  void Sdl2Window::init() {
    FGE_TRACE_ENG("Creating window...");
    if (sdl2WindowCount_s == 0) {
      int32_t glfwInitSuccess = SDL_Init(SDL_INIT_VIDEO);
      FGE_ASSERT_ENG(glfwInitSuccess >= 0, "SDL Error {} | Failed to initialize SDL!", SDL_GetError());
    }
    SDL_version version;
    SDL_GetVersion(&version);
    FGE_INFO_ENG("Using SDL {}.{}.{}!", version.major, version.minor, version.patch);

    SDL_GL_LoadLibrary(nullptr);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    sdl2Window_ = SDL_CreateWindow(
      data_.title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      (int32_t)data_.windowDims.x,
      (int32_t)data_.windowDims.y,
      SDL_WINDOW_OPENGL
    );
    FGE_ASSERT_ENG(sdl2Window_ != nullptr, "SDL Error {} | Failed to create window!", SDL_GetError());
    ++sdl2WindowCount_s;

    FGE_TRACE_ENG("Setting up SDL window data!");
    sdl2Context_ = SDL_GL_CreateContext(sdl2Window_);
    FGE_ASSERT_ENG(sdl2Window_ != nullptr, "SDL Error {} | Failed to create GL context!", SDL_GetError());
    setContextCurrent(true);

    SDL_SetWindowData(sdl2Window_, dataPtrName_.c_str(), &data_);
    setVSync(data_.vSync);
    setFullscreen(data_.fullScreen);
    setCallbacks();

    int32_t gladLoadSuccess = gladLoadGLLoader(SDL_GL_GetProcAddress);
    FGE_ASSERT_ENG(gladLoadSuccess, "Failed to initialize GLAD!");
    FGE_INFO_ENG("Using OpenGL | Vendor: {} | Renderer: {} | Version: {}.{}", 
      glGetString(GL_VENDOR), 
      glGetString(GL_RENDERER),
      glGetString(GL_MAJOR_VERSION),
      glGetString(GL_MINOR_VERSION)
    );

    setContextCurrent(false); // Prepare for context transfer to render thread
    FGE_DEBUG_ENG("Created window: {} ({}, {})", data_.title, data_.windowDims.x, data_.windowDims.y);
  }

  void Sdl2Window::setCallbacks() {}

  void Sdl2Window::shutdown() {
    SDL_DestroyWindow(sdl2Window_);
    --sdl2WindowCount_s;
    if (sdl2WindowCount_s == 0) {
      SDL_FreeSurface(icon_);
      delete iconPixels_;
      SDL_Quit();
    }
  }

  void Sdl2Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
          WindowCloseEvent e{};
          data.eventCallback(e);
          break;
        }
        case SDL_WINDOWEVENT: {
          switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE: {
              WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
              WindowCloseEvent e{};
              data.eventCallback(e);
              break;
            }
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
              WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
              data_.windowDims = {event.window.data1, event.window.data2};
              WindowResizeEvent e{data_.windowDims.x, data_.windowDims.y};
              data.eventCallback(e);
              break;
            }
            case SDL_WINDOWEVENT_MOVED: {
              WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
              data_.windowPos = {event.window.data1, event.window.data2};
              WindowMovedEvent e{data_.windowPos.x, data_.windowPos.y};
              data.eventCallback(e);
              break;
            }
            default: {
              break;
            }
          }
          break;
        }
        case SDL_KEYDOWN: {
          WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
          KeyboardEvent e{
            (event.key.repeat == 0) ? Key::Pressed : Key::Repeat,
            Key::fromNative(event.key.keysym.scancode), 
            event.key.repeat, 
            Modifier::fromNativeBits(static_cast<int32_t>(event.key.keysym.mod))
          };
          data.eventCallback(e);
          break;
        }
        case SDL_KEYUP: {
          WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
          KeyboardEvent e{
            Key::Released,
            Key::fromNative(event.key.keysym.scancode),
            0, 
            Modifier::fromNativeBits(static_cast<int32_t>(event.key.keysym.mod))
          };
          data.eventCallback(e);
          break;
        }
        case SDL_MOUSEBUTTONDOWN: {
          WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
          MouseEvent e{
            Mouse::Pressed,
            Mouse::fromNative(static_cast<int32_t>(event.button.button)),
            Modifier::None
          };
          data.eventCallback(e);
          break;
        }
        case SDL_MOUSEBUTTONUP: {
          WindowState& data = *(WindowState*)SDL_GetWindowData(sdl2Window_, dataPtrName_.c_str());
          MouseEvent e{
            Mouse::Released,
            Mouse::fromNative(static_cast<int32_t>(event.button.button)),
            Modifier::None
          };
          data.eventCallback(e);
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  void Sdl2Window::render() {
    SDL_GL_SwapWindow(sdl2Window_);
    glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  
  void Sdl2Window::dragWindow(vector2_t windowCursorOffset) {
    int32_t x, y;
    SDL_GetWindowPosition(sdl2Window_, &x, &y);
    setPos(x + glm::floor(Input::cursorPos().x) - windowCursorOffset.x, 
           y + glm::floor(Input::cursorPos().y) - windowCursorOffset.y);
  }

  void Sdl2Window::setIcon(uint8_t* image, int32_t width, int32_t height) {
    //https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
    iconPixels_ = new uint8_t{*image};
    icon_ = SDL_CreateRGBSurfaceFrom(
      iconPixels_,
      width, 
      height, 
      32,
      32 * width,
      0x000000ff,
      0x0000ff00,
      0x00ff0000,
      0xff000000
    );
    SDL_SetWindowIcon(sdl2Window_, icon_);
  }

  void Sdl2Window::setPos(double xPos, double yPos) {
    SDL_SetWindowPosition(sdl2Window_, xPos, yPos);
  }

  void Sdl2Window::setVSync(bool enabled) {
    if (enabled) {
      SDL_GL_SetSwapInterval(1);
    } else {
      SDL_GL_SetSwapInterval(0);
    }
    data_.vSync = enabled;
  }

  void Sdl2Window::setFullscreen(bool enabled) {
    if (enabled) {
      SDL_SetWindowFullscreen(sdl2Window_, SDL_WINDOW_FULLSCREEN);
    } else {
      SDL_SetWindowFullscreen(sdl2Window_, 0);
    }
    data_.fullScreen = enabled;
  }

  void Sdl2Window::setContextCurrent(bool current) {
    if (current) {
      FGE_DEBUG_ENG("Making GL context current to thread: {}", std::this_thread::get_id());
      SDL_GL_MakeCurrent(sdl2Window_, sdl2Context_); // not thread safe, so be careful!
    } else {
      FGE_DEBUG_ENG("Making GL context non-current to thread: {}", std::this_thread::get_id());
      SDL_GL_MakeCurrent(sdl2Window_, nullptr); // not thread safe, so be careful!
    }
  }
}