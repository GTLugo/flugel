//
// Created by galex on 5/31/2021.
//

// hallow
#include "color.hpp"
#include "util/color/srgb_transform/srgb_transform.hpp"

namespace Flugel {
  bool Color::using_srgb_color_space = false;

  Color::Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a) {
    if (using_srgb_color_space) {
      to_linear();
    }
  }

  Color::Color(unsigned int hexValue) {
    // RRGGBBAA
    r = static_cast<float>((hexValue >> 24) & 0xFF) / 255.0f;  // Extract the RR byte
    g = static_cast<float>((hexValue >> 16) & 0xFF) / 255.0f;   // Extract the GG byte
    b = static_cast<float>((hexValue >> 8) & 0xFF) / 255.0f;   // Extract the BB byte
    a = static_cast<float>((hexValue) & 0xFF) / 255.0f;   // Extract the AA byte

    if (using_srgb_color_space) {
      to_linear();
    }
  }

  void Color::to_linear() {
    if (!is_linear) {
      r = r_linear();
      g = g_linear();
      b = b_linear();
      is_linear = true;
    }
  }

  void Color::to_srgb() {
    if (is_linear) {
      r = r_srgb();
      g = g_srgb();
      b = b_srgb();
      is_linear = false;
    }
  }

  float Color::r_srgb() { return linearToSrgb(r); }
  float Color::g_srgb() { return linearToSrgb(g); }
  float Color::b_srgb() { return linearToSrgb(b); }
  float Color::r_linear() { return srgbToLinear(r); }
  float Color::g_linear() { return srgbToLinear(g); }
  float Color::b_linear() { return srgbToLinear(b); }
}
