//
// Created by Gabriel Lugo on 3/31/2021.
//
#pragma once

namespace fge {
  struct Color {
    float r, g, b, a;
    bool is_linear = false;
    static bool using_srgb_color_space;

    Color(float r, float g, float b, float a = 1.f);
    explicit Color(u32 hexValue);

    /*hallow_color(const hallow_color& color)
    : r{color.r}, g{color.r}, b{color.b}, a{color.a}, is_linear{color.is_linear} {};
    hallow_color& operator=(const hallow_color& color) {
      hallow_color new_color{0x000000FF};
      return {
        color.r,
        color.g,
        color.b,
        color.a,
        color.is_linear
      };
    }*/

    template<class T>
    T color_rgba() {
      T initializer_list{r, g, b, a};
      return initializer_list;
    }

    template<class T>
    T color_rgb() {
      T initializer_list{r, g, b};
      return initializer_list;
    }

    void to_srgb();
    [[nodiscard]] float r_srgb() const;
    [[nodiscard]] float g_srgb() const;
    [[nodiscard]] float b_srgb() const;

    void to_linear();
    [[nodiscard]] float r_linear() const;
    [[nodiscard]] float g_linear() const;
    [[nodiscard]] float b_linear() const;
  };
}
// Struct based on: https://stackoverflow.com/questions/3723846/convert-from-hex-color-to-rgb-struct-in-c