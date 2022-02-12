#include "uuid.hpp"

#include <utility>

namespace fge {
  u128 UUID::min_value = 0;

  UUID::UUID() 
    : uuid_{Chance::intBetween(min_value, max_value())} {}

  UUID::UUID(u128 uuid)
    : uuid_(std::move(uuid)) {}
}