#pragma once

// Based on TheCherno's implementation of UUID
// https://youtu.be/O_0nUE4S8T8

namespace Flugel {
  class FLUGEL_API UUID {
  public:
    UUID();
    UUID(uint64_t uuid);
    UUID(const UUID&) = default;

    operator uint64_t() const { return uuid_; }
  private:
    uint64_t uuid_;
  };
}

// Allow hashing
namespace std {
  template<>
  struct hash<Flugel::UUID> {
    std::size_t operator()(const Flugel::UUID& uuid) const {
      return hash<uint64_t>()((uint64_t)uuid);
    }
  };
}