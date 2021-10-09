#pragma once

#include "layer.hpp"

namespace fge {
  class FGE_API LayerStack {
    using LayerCollection = std::vector<Layer*>;
  public:
    using iterator = LayerCollection::iterator;
    using const_iterator = LayerCollection::const_iterator;
    using reverse_iterator = LayerCollection::reverse_iterator;
    using const_reverse_iterator = LayerCollection::const_reverse_iterator;
  public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);
    void popLayer(Layer* layer);
    void popOverlay(Layer* overlay);

    iterator begin() { return layers_.begin(); }
    iterator end() { return layers_.end(); }
    reverse_iterator rbegin() { return layers_.rbegin(); }
    reverse_iterator rend() { return layers_.rend(); }

    const_iterator begin() const { return layers_.begin(); }
    const_iterator end() const { return layers_.end(); }
    const_reverse_iterator rbegin() const { return layers_.rbegin(); }
    const_reverse_iterator rend() const { return layers_.rend(); }
  private:
    LayerCollection layers_;
    iterator layerInsert_;
  };
}