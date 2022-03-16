#pragma once

// Based on TheCherno's implementation of UUID
// https://youtu.be/O_0nUE4S8T8

namespace ff {
  class UUID {
  public:
    UUID()
      : uuid_{Random::intBetween(std::numeric_limits<u128>::min(), std::numeric_limits<u128>::max())} {}
    explicit UUID(u128 uuid)
      : uuid_(std::move(uuid)) {}
    UUID(const UUID&) = default;

    explicit operator u128() const { return uuid_; }
    friend std::ostream& operator<<(std::ostream& o, const UUID& uuid) {
      return o << uuid.uuid_;
    }
  private:
    u128 uuid_;
  };
}

// Allow hashing
namespace std {
  template<>
  struct hash<ff::UUID> {
    std::size_t operator()(const ff::UUID& uuid) const {
      return hash<ff::u128>()((ff::u128)uuid);
    }
  };
}