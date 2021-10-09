#include "layer.hpp"

namespace Flugel {
  Layer::Layer(const std::string& name)
    : name_{name} {}
  
  Layer::~Layer() {}

  bool Layer::onAppEvent(AppEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case AppEventType::UpdateFixed: {
        updateFixed();
        return true;
      }
      case AppEventType::Update: {
        update();
        return true;
      }
      case AppEventType::Render: {
        render();
        return true;
      }
      default: {
        return false;
      }
    }
  }

  bool Layer::onWindowEvent(WindowEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false;
  }

  bool Layer::onKeyboardEvent(KeyboardEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onMouseEvent(MouseEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    // custom dragging and close button
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onCursorEvent(CursorEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onScrollEvent(ScrollEvent& e) {
    //FLUGEL_DEBUG_E("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return false; // return false so event isn't marked handled from base app
  }
}