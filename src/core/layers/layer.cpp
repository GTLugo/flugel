#include "layer.hpp"

namespace ff {
  Layer::Layer(std::string name)
    : name_{std::move(name)} {}
  
  Layer::~Layer() {
    Log::trace_e("Destructing layer: {0}...", name_);
  }

  bool Layer::onAppEvent_eng(const AppEvent& e) {
    return appNotifier_.notify(e) || onAppEvent(e);
  }

  bool Layer::onLogicEvent_eng(const LogicEvent& e) {
    return logicNotifier_.notify(e) || onLogicEvent(e);
  }

  bool Layer::onRenderEvent_eng(const RenderEvent& e) {
    return renderNotifier_.notify(e) || onRenderEvent(e);
  }

  bool Layer::onWindowEvent_eng(const WindowEvent& e) {
    return windowNotifier_.notify(e) || onWindowEvent(e);
  }

  bool Layer::onKeyboardEvent_eng(const KeyboardEvent& e) {
    return keyNotifier_.notify(e) || onKeyboardEvent(e);
  }

  bool Layer::onMouseEvent_eng(const MouseEvent& e) {
    return mouseNotifier_.notify(e) || onMouseEvent(e);
  }

  bool Layer::onCursorEvent_eng(const CursorEvent& e) {
    return cursorNotifier_.notify(e) || onCursorEvent(e);
  }

  bool Layer::onScrollEvent_eng(const ScrollEvent& e) {
    return scrollNotifier_.notify(e) || onScrollEvent(e);
  }
}