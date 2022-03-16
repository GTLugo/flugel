#include "mouse_codes.hpp"

namespace ff{
  std::map<Mouse::Code, std::string> Mouse::nameMap_{
    {Mouse::Unknown, "Unknown"},
    {Mouse::_1,      "Mouse1"}, 
    {Mouse::_2,      "Mouse2"}, 
    {Mouse::_3,      "Mouse3"}, 
    {Mouse::_4,      "Mouse4"}, 
    {Mouse::_5,      "Mouse5"},
    {Mouse::_6,      "Mouse6"},
    {Mouse::_7,      "Mouse7"},
    {Mouse::_8,      "Mouse8"},

    {Mouse::Left,    "MouseLeft"},
    {Mouse::Right,   "MouseRight"},
    {Mouse::Middle,  "MouseMiddle"},
    {Mouse::Back,    "MouseBack"},
    {Mouse::Forward, "MouseForward"},
  };
}
  