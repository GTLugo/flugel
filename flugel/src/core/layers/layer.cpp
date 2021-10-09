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
        updateFixed();
        return false;
      }
      case AppEventType::Update: {
        update();
        return false;
      }
      case AppEventType::Render: {
        render();
        return false;
      }
      default: {
        return false;
      }
    }
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