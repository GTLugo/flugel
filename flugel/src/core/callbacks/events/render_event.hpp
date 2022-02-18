#pragma once

#include "event.hpp"

namespace fge {

  class FGE_API RenderEvent : public Event {
  public:
    enum Action {
      None = 0,
      Start, BeginFrame, EndFrame, BeginImGui, EndImGui, Stop, // Render thread
    };

    explicit RenderEvent(Action action)
        : action_{action} {}
    
    EVENT_TYPE(Event::Type::Render)

    [[nodiscard]] Action action() const { return action_; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> ";
      switch (action_) {
        case Action::Start:
          ss << "(START)";
          break;
        case Action::BeginFrame:
          ss << "(BEGIN_FRAME)";
          break;
        case Action::EndFrame:
          ss << "(END_FRAME)";
          break;
        case Action::BeginImGui:
          ss << "(BEGIN_IMGUI)";
          break;
        case Action::EndImGui:
          ss << "(END_IMGUI)";
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