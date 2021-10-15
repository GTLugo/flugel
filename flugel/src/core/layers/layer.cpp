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
      // case AppEventType::Start: {
      //   //onStartEvent(dynamic_cast<AppStartEvent&>(e));
      //   return false;
      // }
      default: {
        return false;
      }
    }
  }

  // void Layer::onStartEvent(AppStartEvent& e) {
  //   //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
  // }

  // void Layer::onFixedUpdateEvent(AppFixedUpdateEvent& e) {
  //   //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
  // }

  // void Layer::onUpdateEvent(AppUpdateEvent& e) {
  //   //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
  // }

  // void Layer::onRenderEvent(AppRenderEvent& e) {
  //   //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
  // }

  // void Layer::onEndEvent(AppEndEvent& e) {
  //   //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
  // }

  bool Layer::onWindowEvent(WindowEvent& e) {
    //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
    
    return false;
  }

  bool Layer::onKeyboardEvent(KeyboardEvent& e) {
    //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);

    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onMouseEvent(MouseEvent& e) {
    //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
    // custom dragging and close button
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onCursorEvent(CursorEvent& e) {
    //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
    
    return false; // return false so event isn't marked handled from base app
  }

  bool Layer::onScrollEvent(ScrollEvent& e) {
    //FGE_DEBUG_ENG("Layer: {0} | {1}", name_, e);
    
    return false; // return false so event isn't marked handled from base app
  }
}