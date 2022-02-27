#include "layer.hpp"

namespace fge {
  Layer::Layer(std::string name)
    : name_{std::move(name)} {}
  
  Layer::~Layer() {
    FGE_TRACE_ENG("Destructing layer: {0}...", name_);
  }
}