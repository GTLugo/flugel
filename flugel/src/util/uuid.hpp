#pragma once


// Based on TheCherno's implementation of UUID
// https://youtu.be/O_0nUE4S8T8

namespace fge {
  class FGE_API UUID {
  public:
    UUID();
    explicit UUID(u128 uuid);
    UUID(const UUID&) = default;

    explicit operator u128() const { return uuid_; }
  private:
    u128 uuid_;
    static u128 min_value;
    static u128& max_value() {
      static u128 max_value = static_cast<u128>(pow(2,128) - 1);
      return max_value;
    }
  };
}

// Allow hashing
namespace std {
  template<>
  struct hash<fge::UUID> {
    std::size_t operator()(const fge::UUID& uuid) const {
      return hash<fge::u128>()((fge::u128)uuid);
    }
  };
}