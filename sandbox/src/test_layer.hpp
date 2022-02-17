#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer : public fge::Layer {
    using Input = fge::Input;
    using Key = fge::Key;
    using Modifier = fge::Modifier;
  public:
    TestLayer()
      : Layer{"test_layer"} {
      FGE_DEBUG("{}", fge::UUID{});
    }

    bool onLogicEvent(fge::LogicEvent& e) override {
//      switch (e.type()) {
//        case fge::LogicEventType::Tick: {
//          if (Input::isPressed(Key::Space)) {
//            FGE_TRACE("{}", (Input::isPressed(Modifier::Shift|Modifier::Control)) ? "OwO" : "UwU");
//          }
//        }
//        default: break;
//      }
      return false;
    }

    bool onMouseEvent(fge::MouseEvent& e) override {
      //FGE_DEBUG("{}: {}", name_, e);
      return false;
    }

    bool onKeyboardEvent(fge::KeyboardEvent& e) override {
      //FGE_DEBUG("{}: {}", name_, e);
      std::string input{"hello\n { everyone i am cat girl"};
      std::stringstream inputStream{input};
      std::stringstream outputStream;
      std::string input2, input3;
      std::string nextInput;
      inputStream >> input2 >> input3 >> nextInput;
      while (inputStream) {
        outputStream << nextInput << " ";
        inputStream >> nextInput;
      }

      FGE_DEBUG("\n{}\n{}\n{}\n{}", input2, input3, inputStream.str(), outputStream.str());
      return false;
    }
  };
}