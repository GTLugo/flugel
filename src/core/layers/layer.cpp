#include "layer.hpp"

namespace ff {
  Layer::Layer(std::string name)
    : name_{std::move(name)} {}
  
  Layer::~Layer() {
    Log::trace_e("Destructing layer: {0}...", name_);
  }
}