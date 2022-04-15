#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace ff {
  class EventBase {
  public:
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual bool wasHandled() const { return wasHandled_; }
    virtual void setHandled() const { wasHandled_ = true; }
  protected:
    mutable bool wasHandled_{false};
  };

  inline std::ostream& operator<<(std::ostream& out, const EventBase& e) {
    return out << e.toString();
  }
}