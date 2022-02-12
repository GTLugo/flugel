#include "uuid.hpp"

namespace fge {
  static std::random_device randomDevice_s;
  static std::mt19937_64 randomEngine_s{randomDevice_s()};
  static std::uniform_int_distribution<u64> uniformDist_s;

  UUID::UUID() 
    : uuid_{uniformDist_s(randomEngine_s)} {
    
  }

  UUID::UUID(u64 uuid) {

  } 
}