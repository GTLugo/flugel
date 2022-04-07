#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace ff {
  class EventBase {
  public:
    enum class Type {
      None       = 0,
      Window     = BIT(0),
      MainThread = BIT(1),
      GameThread = BIT(2),
      Input      = BIT(3),
    };

    [[nodiscard]] virtual Type type() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] virtual bool wasHandled() const { return wasHandled_; }

  protected:
    mutable bool wasHandled_{false};
  };

  inline std::ostream& operator<<(std::ostream& out, const EventBase& e) {
    return out << e.toString();
  }
}