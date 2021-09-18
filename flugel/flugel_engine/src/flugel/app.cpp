#include "app.hpp"

#include "events/app_event.hpp"

namespace Flugel {
  App::App() {

  }

  App::~App() {

  }

  void App::run() {
    FLUGEL_INFO("Running...");
    TimePoint previousTime{}, currentTime{};
    Second elapsedTime{};

    int x = 0;
    while (x < 1000) {
      currentTime = Clock::now();
      Second deltaTime = currentTime - previousTime;

      std::stringstream ss;
      ss << "FPS (" << 1.0 / deltaTime.count() << ")";
      elapsedTime += deltaTime;
      if (elapsedTime.count() >= 1) {
        FLUGEL_DEBUG(ss.str());

        WindowResizeEvent e(800, 450);
        FLUGEL_TRACE(e);
        
        elapsedTime = Second::zero();
      }
      
      previousTime = currentTime;
    }
    FLUGEL_INFO("Finished running!");

    // #ifndef NDEBUG
    // FLUGEL_INFO_ENGINE("Press ENTER to continue...");
    // std::cin.get();
    // #endif
  }
}