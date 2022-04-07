//
// Created by galex on 4/7/2022.
//

#pragma once

#include "event.hpp"
#include "core/input/key_codes.hpp"
#include "core/input/mouse_codes.hpp"

namespace ff {
  class InputEventBase : public EventBase {
  public:
    enum Action {
      None = 0,
      Keyboard, Mouse, Scroll, Cursor,
    };

    [[nodiscard]] EventBase::Type type() const override { return EventBase::Type::Input; }
    [[nodiscard]] Action action() const { return action_; }
    [[nodiscard]] std::string toString() const override {
      std::string name{"<INPUT> "};
      switch (action_) {
        case Action::Keyboard: return name + "KEYBOARD";
        case Action::Mouse:    return name + "MOUSE";
        case Action::Scroll:   return name + "SCROLL";
        case Action::Cursor:   return name + "CURSOR";
        default:               return name + "UNKNOWN";
      }
    }
  protected:
    const Action action_;

    explicit InputEventBase(Action action) : action_{action} {}
  };

  class InputKeyEvent : public InputEventBase {
  public:
    InputKeyEvent(Key::State keyState, Key::Code key, i32 repeatCount, Modifier::BitCodes mods)
        : InputEventBase{Action::Keyboard}, keyState_{keyState}, key_{key}, repeatCount_{repeatCount}, mods_{mods} {}

    /// TODO: Move button state to input enum. Add Held state for key
    [[nodiscard]] Key::State keyState() const { return keyState_; }
    [[nodiscard]] Key::Code key() const { return key_; }
    [[nodiscard]] i32 repeatCount() const { return repeatCount_; }
    [[nodiscard]] Modifier::BitCodes mods() const { return mods_; }

    template<Key::Code K>
    [[nodiscard]] bool test(Key::State state) const { return key_ == K && keyState_ == state; }
    template<Modifier::Code M>
    [[nodiscard]] bool test(Key::State state) const { return (state == Key::Released) ? !(mods_ & M) : mods_ & M; }

    [[nodiscard]] std::string toString() const override {
      return InputEventBase::toString() + " (" + Key::toString(keyState_) + ": "
             + Key::toString(key_) + ", " + std::to_string(mods_) + ")";
    }
  protected:
    const Key::State keyState_;
    const Key::Code key_;
    const i32 repeatCount_;
    const Modifier::BitCodes mods_;
  };

  class InputMouseEvent : public InputEventBase {
  public:
    InputMouseEvent(Mouse::State buttonState, Mouse::Code button, Modifier::BitCodes mods)
        : InputEventBase{Action::Mouse}, buttonState_{buttonState}, button_{button}, mods_{mods} {}

    /// TODO: Move button state to input enum. Add Held state for key
    [[nodiscard]] Mouse::State buttonState() const { return buttonState_; }
    [[nodiscard]] Mouse::Code button() const { return button_; }
    [[nodiscard]] Modifier::BitCodes mods() const { return mods_; }

    template<Mouse::Code B>
    [[nodiscard]] bool test(Mouse::State state) const { return button_ == B && buttonState_ == state; }

    [[nodiscard]] std::string toString() const override {
      return InputEventBase::toString() + " (" + Mouse::toString(buttonState_) + ": "
          + Mouse::toString(button_) + ", " + std::to_string(mods_) + ")";
    }
  protected:
    Mouse::State buttonState_;
    Mouse::Code button_;
    Modifier::BitCodes mods_;
  };

  class InputCursorEvent : public InputEventBase {
  public:

    InputCursorEvent(double xPos, double yPos)
        : InputEventBase{Action::Cursor}, xPos_{xPos}, yPos_{yPos} {}

    [[nodiscard]] double xPos() const { return xPos_; }
    [[nodiscard]] double yPos() const { return yPos_; }

    [[nodiscard]] std::string toString() const override {
      return InputEventBase::toString() + " (" + std::to_string(xPos_) + ", " + std::to_string(yPos_) + ")";
    }
  protected:
    double xPos_, yPos_;
  };

  class InputScrollEvent : public InputEventBase {
  public:
    InputScrollEvent(double xOffset, double yOffset)
        : InputEventBase{Action::Scroll}, xOffset_{xOffset}, yOffset_{yOffset} {}

    [[nodiscard]] double xOffset() const { return xOffset_; }
    [[nodiscard]] double yOffset() const { return yOffset_; }

    [[nodiscard]] std::string toString() const override {
      return InputEventBase::toString() + " (" + std::to_string(xOffset_) + ", " + std::to_string(yOffset_) + ")";
    }
  protected:
    const double xOffset_, yOffset_;
  };
}

