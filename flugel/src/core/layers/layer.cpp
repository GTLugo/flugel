#include "layer.hpp"

namespace fge {
  Layer::Layer(const std::string& name)
    : name_{name} {}
  
  Layer::~Layer() {
    FGE_TRACE_ENG("Destructing layer: {0}...", name_);
  }

  bool Layer::onAppEvent(AppEvent& e) {
    //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
    switch (e.type()) {
      case AppEventType::UpdateFixed: {
        onUpdateFixedEvent(dynamic_cast<AppUpdateFixedEvent&>(e));
        return false;
      }
      case AppEventType::Update: {
        onUpdateEvent(dynamic_cast<AppUpdateEvent&>(e));
        return false;
      }
      case AppEventType::Render: {
        onRenderEvent(dynamic_cast<AppRenderEvent&>(e));
        return false;
      }
      default: {
        return false;
      }
    }
  }

  void Layer::onUpdateFixedEvent(AppUpdateFixedEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
  }

  void Layer::onUpdateEvent(AppUpdateEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
  }

  void Layer::onRenderEvent(AppRenderEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
  }

  bool Layer::onWindowEvent(WindowEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false;
  }

  bool Layer::onKeyboardEvent(KeyboardEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));

    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onMouseEvent(MouseEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    // custom dragging and close button
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onCursorEvent(CursorEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onScrollEvent(ScrollEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }
}