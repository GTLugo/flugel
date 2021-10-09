#include "layer_stack.hpp"

namespace fge {
  LayerStack::~LayerStack() {
    for (Layer* layer : layers_) {
      layer->detach();
      delete layer;
    }
  }

  void LayerStack::pushLayer(Layer* layer) {
    layers_.emplace(begin() + layerInsertIndex_++, layer);
  }

  void LayerStack::pushOverlay(Layer* overlay) {
    layers_.emplace_back(overlay);
  }

  void LayerStack::popLayer(Layer* layer) {
    auto itr = std::find(begin(), end(), layer);
    if (itr != begin() + layerInsertIndex_) {
      layer->detach();
      layers_.erase(itr);
      --layerInsertIndex_;
    }
  }

  void LayerStack::popOverlay(Layer* overlay) {
    auto itr = std::find(begin(), end(), overlay);
    if (itr != end()) {
      overlay->detach();
      layers_.erase(itr);
    }
  }
}