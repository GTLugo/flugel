#pragma once
//
// Created by galex on 12/11/2021.
//


namespace fge {
  class Chance {
    using random_device = boost::random::random_device;
    template<class T>
    using uniform_real_dist = boost::random::uniform_real_distribution<T>;
    template<class T>
    using uniform_int_dist = boost::random::uniform_int_distribution<T>;
    template<class T>
    using normal_dist = boost::random::normal_distribution<T>;

  public:
    template<class T>
    [[nodiscard]] static T roll(T sides) {
      return intBetween(1, static_cast<T>(sides));
    }

    [[nodiscard]] static bool flip() {
      return roll(2) - 1;
    }

    template<class T>
    [[nodiscard]] static T realBetween(T lowerIncl, T upperExcl) {
      uniform_real_dist<T> dist(lowerIncl, upperExcl);
      return dist(randomDevice());
    }

    template<class T>
    [[nodiscard]] static T intBetween(T lowerIncl, T upperIncl) {
      uniform_int_dist<T> dist(lowerIncl, upperIncl);
      return dist(randomDevice());
    }

    template<class T>
    [[nodiscard]] static T normal(T mean, T stddev) {
      normal_dist<T> dist(mean, stddev);
      return dist(randomDevice());
    }

    template<class T>
    [[nodiscard]] static float normalBetween(T mean, T stddev, T lowerIncl, T upperIncl) {
      return boost::algorithm::clamp(normal(mean, stddev), lowerIncl, upperIncl);
    }

  private:
    static random_device& randomDevice() {
      static random_device device;
      return device;
    }
  };
}