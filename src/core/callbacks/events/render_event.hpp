#pragma once

#include "event.hpp"

namespace ff {

  class RenderEvent : public Event {
  public:
    enum Action { // Order of Render thread
      None = 0,
      Awake, Start, Stop,
      BeginFrame, AppStep, ImGuiStep, EndFrame,
    };

    RenderEvent(Action action)
        : action_{action} {}
    
    EVENT_TYPE(Event::Type::Render)

    [[nodiscard]] Action action() const { return action_; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> ";
      switch (action_) {
        case Action::Awake:
          ss << "(AWAKE)";
          break;
        case Action::Start:
          ss << "(START)";
          break;
        case Action::BeginFrame:
          ss << "(BEGIN_FRAME)";
          break;
        case Action::AppStep:
          ss << "(APP)";
          break;
        case Action::ImGuiStep:
          ss << "(IMGUI)";
          break;
        case Action::EndFrame:
          ss << "(END_FRAME)";
          break;
        case Action::Stop:
          ss << "(STOP)";
          break;
        default:
          ss << "(UNKNOWN)";
          break;
      }
      return ss.str();
    }
  protected:
    const Action action_;
  };
}