//
// Created by galex on 3/31/2022.
//

#pragma once

namespace ff {

  class ComponentBase {
  public:
    static const inline size_t maxComponents{512};
    using ID = size_t;

    ComponentBase() = default;
    virtual ~ComponentBase() = default;

    [[nodiscard]] static ID componentCount() { return componentCount_; }
  protected:
    static inline size_t componentCount_{0};
  };

  template<class C>
  class Component : public ComponentBase {
    friend class ECSManager;
  public:
    [[nodiscard]] static ID id() { return id_; }
  private:
    static const inline ID id_{componentCount_++};
  };
}

