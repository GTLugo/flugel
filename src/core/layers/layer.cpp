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

  bool Layer::onRenderEvent_eng(const RenderEvent& e) {
    return renderNotifier_.notify(e) || onRenderEvent(e);
  }

  bool Layer::onLogicEvent_eng(const LogicEvent& e) {
    return logicNotifier_.notify(e) || onLogicEvent(e);
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

  template<>
  UUID Layer::subscribe<AppEvent>(Notifier<AppEvent>::EventFn eventFn) {
    return appNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<RenderEvent>(Notifier<RenderEvent>::EventFn eventFn) {
    return renderNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<LogicEvent>(Notifier<LogicEvent>::EventFn eventFn) {
    return logicNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<WindowEvent>(Notifier<WindowEvent>::EventFn eventFn) {
    return windowNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<KeyboardEvent>(Notifier<KeyboardEvent>::EventFn eventFn) {
    return keyNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<MouseEvent>(Notifier<MouseEvent>::EventFn eventFn) {
    return mouseNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<CursorEvent>(Notifier<CursorEvent>::EventFn eventFn) {
    return cursorNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  UUID Layer::subscribe<ScrollEvent>(Notifier<ScrollEvent>::EventFn eventFn) {
    return scrollNotifier_.subscribe(std::move(eventFn));
  }

  template<>
  void Layer::unsubscribe<AppEvent>(const UUID& id) {
    appNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<RenderEvent>(const UUID& id) {
    renderNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<LogicEvent>(const UUID& id) {
    logicNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<WindowEvent>(const UUID& id) {
    windowNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<KeyboardEvent>(const UUID& id) {
    keyNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<MouseEvent>(const UUID& id) {
    mouseNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<CursorEvent>(const UUID& id) {
    cursorNotifier_.unsubscribe(id);
  }

  template<>
  void Layer::unsubscribe<ScrollEvent>(const UUID& id) {
    scrollNotifier_.unsubscribe(id);
  }
}