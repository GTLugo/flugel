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
      //   return onStartEvent(dynamic_cast<AppStartEvent&>(e));
      // }
      // case AppEventType::MainStart: {
      //   return onMainStartEvent(dynamic_cast<AppMainStartEvent&>(e));
      // }
      // case AppEventType::RenderStart: {
      //   return onRenderStartEvent(dynamic_cast<AppRenderStartEvent&>(e));
      // }
      // case AppEventType::Poll: {
      //   return onPollEvent(dynamic_cast<AppPollEvent&>(e));
      // }
      // case AppEventType::FixedUpdate: {
      //   return onFixedUpdateEvent(dynamic_cast<AppFixedUpdateEvent&>(e));
      // }
      // case AppEventType::Update: {
      //   return onUpdateEvent(dynamic_cast<AppUpdateEvent&>(e));
      // }
      // case AppEventType::MainUpdate: {
      //   return onMainUpdateEvent(dynamic_cast<AppMainUpdateEvent&>(e));
      // }
      // case AppEventType::RenderUpdate: {
      //   return onRenderUpdateEvent(dynamic_cast<AppRenderUpdateEvent&>(e));
      // }
      // case AppEventType::End: {
      //   return onEndEvent(dynamic_cast<AppEndEvent&>(e));
      // }
      // case AppEventType::MainEnd: {
      //   return onMainEndEvent(dynamic_cast<AppMainEndEvent&>(e));
      // }
      // case AppEventType::RenderEnd: {
      //   return onRenderEndEvent(dynamic_cast<AppRenderEndEvent&>(e));
      // }
      default: {
        return false;
      }
    }
  }
}