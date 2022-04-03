#include "layer_stack.hpp"

namespace ff {
  LayerStack::~LayerStack() {
    for (auto ritr = rbegin(); ritr != rend(); ++ritr) {
      (*ritr)->detach();
      delete (*ritr);
    }
  }

  void LayerStack::pushLayer(Layer* layer) {
    layers_.emplace(begin() + layerInsertIndex_++, layer);
    layer->attach();
  }

  void LayerStack::pushOverlay(Layer* overlay) {
    layers_.emplace(begin() + layerInsertIndex_ + overlayInsertIndex_++, overlay);
    overlay->attach();
  }

  void LayerStack::pushBottomStack(Layer* layer) {
    layers_.emplace_back(layer);
    layer->attach();
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
    if (itr != begin() + layerInsertIndex_ + overlayInsertIndex_) {
      overlay->detach();
      layers_.erase(itr);
      --overlayInsertIndex_;
    }
  }

  void LayerStack::popBottomStack(Layer* layer) {
    auto itr = std::find(begin(), end(), layer);
    if (itr != end()) {
      layer->detach();
      layers_.erase(itr);
    }
  }
}