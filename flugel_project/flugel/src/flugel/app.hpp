#pragma once

#include "core.hpp"

namespace Flugel {
  class FLUGEL_API App {
    public:
      App();
      virtual ~App();

      void run();
    private:
  };

  // To be defined in project app
  App* CreateApp();
}