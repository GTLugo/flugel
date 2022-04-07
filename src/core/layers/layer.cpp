#include "layer.hpp"

namespace ff {
  Layer::Layer(std::string name)
    : name_{std::move(name)} {}
  
  Layer::~Layer() {
    Log::trace_e("Destructing layer: {0}...", name_);
  }

  bool Layer::onMainEvent_eng(const MainEvent& e) {
    return mainNotifier_.notify(e) || onMainEvent(e);
  }

  bool Layer::onGameEvent_eng(const GameEvent& e) {
    return gameNotifier_.notify(e) || onGameEvent(e);
  }

  bool Layer::onWindowEvent_eng(const WindowEvent& e) {
    return windowNotifier_.notify(e) || onWindowEvent(e);
  }

  bool Layer::onInputEvent_eng(const InputEvent& e) {
    return inputNotifier_.notify(e) || onInputEvent(e);
  }
}