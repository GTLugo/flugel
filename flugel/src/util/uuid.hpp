#pragma once

// Based on TheCherno's implementation of UUID
// https://youtu.be/O_0nUE4S8T8

namespace fge {
  class FGE_API UUID {
  public:
    UUID();
    UUID(u64 uuid);
    UUID(const UUID&) = default;

    operator u64() const { return uuid_; }
  private:
    u64 uuid_;
  };
}

// Allow hashing
namespace std {
  template<>
  struct hash<fge::UUID> {
    std::size_t operator()(const fge::UUID& uuid) const {
      return hash<u64>()((u64)uuid);
    }
  };
}