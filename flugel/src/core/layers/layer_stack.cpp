#include "layer_stack.hpp"

namespace Flugel {
  LayerStack::LayerStack() {
    layerInsert_ = begin();
  }

  LayerStack::~LayerStack() {
    for (Layer* layer : layers_) {
      delete layer;
    }
  }

  void LayerStack::pushLayer(Layer* layer) {
    layerInsert_ = layers_.emplace(layerInsert_, layer);
  }

  void LayerStack::pushOverlay(Layer* overlay) {
    layers_.emplace_back(overlay);
  }

  void LayerStack::popLayer(Layer* layer) {
    auto itr = std::find(begin(), end(), layer);
    if (itr != end()) {
      layers_.erase(itr);
      --layerInsert_;
    }
  }

  void LayerStack::popOverlay(Layer* overlay) {
    auto itr = std::find(begin(), end(), overlay);
    if (itr != end()) {
      layers_.erase(itr);
    }
  }
}