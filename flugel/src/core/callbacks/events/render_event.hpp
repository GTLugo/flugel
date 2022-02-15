#pragma once

#include "event.hpp"

namespace fge {
  enum class RenderEventType {
    None = 0,
    Start, BeginFrame, EndFrame, BeginImGui, EndImGui, Stop, // Render thread
  };

  class FGE_API RenderEvent : public Event {
  public:
    EVENT_CATEGORY(Event::Category::Render)

    RenderEventType type() const { return type_; }
  protected:
    const RenderEventType type_;
    
    RenderEvent(RenderEventType type)
      : type_{type} {}
  };

  class FGE_API RenderStartEvent : public RenderEvent {
  public:
    RenderStartEvent()
      : RenderEvent{RenderEventType::Start} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> (START)";
      return ss.str();
    }
  };

  class FGE_API RenderBeginFrameEvent : public RenderEvent {
  public:
    RenderBeginFrameEvent()
      : RenderEvent{RenderEventType::BeginFrame} {}

    /// TODO: Complete copy assignment
    RenderBeginFrameEvent(const RenderBeginFrameEvent& e)
      : RenderEvent{RenderEventType::BeginFrame} {}

    /// TODO: Complete copy assignment
    RenderBeginFrameEvent& operator=(const RenderBeginFrameEvent& e) {
      return *this;
    }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> (BEGIN_FRAME)";
      return ss.str();
    }
  };

  class FGE_API RenderEndFrameEvent : public RenderEvent {
  public:
    RenderEndFrameEvent()
      : RenderEvent{RenderEventType::EndFrame} {}

    /// TODO: Complete copy assignment
    RenderEndFrameEvent(const RenderEndFrameEvent& e)
      : RenderEvent{RenderEventType::EndFrame} {}

    /// TODO: Complete copy assignment
    RenderEndFrameEvent& operator=(const RenderEndFrameEvent& e) {
      return *this;
    }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> (END_FRAME)";
      return ss.str();
    }
  };

  class FGE_API RenderBeginImGuiEvent : public RenderEvent {
  public:
    RenderBeginImGuiEvent()
      : RenderEvent{RenderEventType::BeginImGui} {}

    /// TODO: Complete copy assignment
    RenderBeginImGuiEvent(const RenderBeginImGuiEvent& e)
      : RenderEvent{RenderEventType::BeginImGui} {}

    /// TODO: Complete copy assignment
    RenderBeginImGuiEvent& operator=(const RenderBeginImGuiEvent& e) {
      return *this;
    }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> (BEGIN_IMGUI)";
      return ss.str();
    }
  };

  class FGE_API RenderEndImGuiEvent : public RenderEvent {
  public:
    RenderEndImGuiEvent()
      : RenderEvent{RenderEventType::EndImGui} {}

    /// TODO: Complete copy assignment
    RenderEndImGuiEvent(const RenderEndImGuiEvent& e)
      : RenderEvent{RenderEventType::EndImGui} {}

    /// TODO: Complete copy assignment
    RenderEndImGuiEvent& operator=(const RenderEndImGuiEvent& e) {
      return *this;
    }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> (END_IMGUI)";
      return ss.str();
    }
  };

  class FGE_API RenderStopEvent : public RenderEvent {
  public:
    RenderStopEvent()
      : RenderEvent{RenderEventType::Stop} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Render> (STOP)";
      return ss.str();
    }
  };
}