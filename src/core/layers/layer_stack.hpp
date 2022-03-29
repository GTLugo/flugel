#pragma once

#include "layer.hpp"

namespace ff {
  // Engine,
  // ...(AppLayers)...,
  // ...(AppOverlays)...,
  // ImGui,
  // Render
  class LayerStack {
    using LayerCollection = std::vector<Layer*>;
  public:
    using iterator = LayerCollection::iterator;
    using const_iterator = LayerCollection::const_iterator;
    using reverse_iterator = LayerCollection::reverse_iterator;
    using const_reverse_iterator = LayerCollection::const_reverse_iterator;
  public:
    LayerStack() = default;
    ~LayerStack();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);
    void popLayer(Layer* layer);
    void popOverlay(Layer* overlay);
    void pushBottomStack(Layer* layer);
    void popBottomStack(Layer* layer);

    [[nodiscard]] iterator begin() { return layers_.begin(); }
    [[nodiscard]] iterator end() { return layers_.end(); }
    [[nodiscard]] reverse_iterator rbegin() { return layers_.rbegin(); }
    [[nodiscard]] reverse_iterator rend() { return layers_.rend(); }

    [[nodiscard]] const_iterator begin() const { return layers_.begin(); }
    [[nodiscard]] const_iterator end() const { return layers_.end(); }
    [[nodiscard]] const_reverse_iterator rbegin() const { return layers_.rbegin(); }
    [[nodiscard]] const_reverse_iterator rend() const { return layers_.rend(); }
  private:
    LayerCollection layers_;
		u32 layerInsertIndex_{0};
    u32 overlayInsertIndex_{0};
  };
}