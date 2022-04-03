//
// Created by galex on 3/31/2022.
//
// Sources
// https://austinmorlan.com/posts/entity_component_system/
// https://indiegamedev.net/2020/05/19/an-entity-component-system-with-data-locality-in-cpp/
// https://skypjack.github.io/2019-02-14-ecs-baf-part-1/
// https://www.youtube.com/watch?v=W3aieHjyNvw

#pragma once

#include "core/ecs/components/component.hpp"
#include "core/threading/concurrent_queue.hpp"

#include <boost/unordered_map.hpp>

namespace ff {

  struct Entity {
  public:
    using ID = UUID;
    using BitSet = std::bitset<ComponentBase::maxComponents>;

    explicit Entity(ECSManager* ecsManager);

    ~Entity();

    [[nodiscard]] ID id() const { return id_; }

    [[nodiscard]] const Entity::BitSet& components() const;

    template<class C>
    Entity& addComponent(C component);

    template<class C>
    Entity& removeComponent();

    template<class C>
    C& component();

    bool operator<(const Entity& rhs) const { return id_ < rhs.id_; }

    bool operator==(const Entity& rhs) const { return id_ == rhs.id_; }

  private:
    ID id_{};
    ECSManager* ecsManager_;
  };
}

// Allow hashing
namespace std {
  template<>
  struct hash<ff::Entity> {
    std::size_t operator()(const ff::Entity& entity) const {
      return boost::hash<boost::uuids::uuid>()(entity.id());
    }
  };
}

namespace ff {
  class SystemBase {
  public:
    virtual ~SystemBase() = default;

    std::unordered_map<Entity::ID, Entity> entities{};
    [[nodiscard]] const Entity::BitSet& components() const { return bitSet_; }

    virtual void onUpdate() = 0;

  protected:
    Entity::BitSet bitSet_{};
  };

  template<class FirstComponent, class... Components>
  class System : public SystemBase {
  public:
    System() {
      // https://www.fluentcpp.com/2021/03/12/cpp-fold-expressions/
      (bitSet_.set(Component<FirstComponent>::id(), true), ..., bitSet_.set(Component<Components>::id(), true));
    }
  };

  class ECSManager {
    class ComponentMapBase {
    public:
      virtual ~ComponentMapBase() = default;
      virtual void onEntityRemoved(const Entity& entity) = 0;
    };

    template<class C>
    class ComponentMap : public ComponentMapBase {
    public:
      void add(const Entity& entity, C component) {
        FF_ASSERT_E(!entityToComponent_.contains(entity.id()), "Attempted component override upon existent data.");
        Log::debug_e(R"(Adding component "{0}" to entity "{1}")", typeid(C).name(), entity.id());

        entityToComponent_[entity.id()] = components_.size();
        componentToEntity_[components_.size()] = entity.id();
        components_.push_back(std::move(component));
      }

      void remove(const Entity& entity) {
        FF_ASSERT_E(entityToComponent_.contains(entity.id()), "Attempted component removal upon non-existent data.");
        Log::debug_e(R"(Removing component "{0}" from entity "{1}")", typeid(C).name(), entity.id());

        // retrieve IDs
        size_t indexTarget{entityToComponent_[entity.id()]};
        size_t indexLast{components_.size() - 1};
        Entity::ID entityLast{componentToEntity_[indexLast]};

        // move target to end of map
        std::iter_swap(components_.begin() + indexTarget, components_.begin() + indexLast);
        entityToComponent_[entityLast] = indexTarget;
        componentToEntity_[indexTarget] = entityLast;

        // pop end of map
        entityToComponent_.erase(entity.id());
        componentToEntity_.erase(indexLast);
        components_.pop_back();
      }

      C& data(const Entity& entity) {
        //Log::debug_e(R"(Accessing component "{0}" on entity "{1}")", typeid(C).name(), entity.id());
        FF_ASSERT_E(entityToComponent_.contains(entity.id()), "Attempted component access of non-existent data.");
        return components_[entityToComponent_[entity.id()]];
      }

      void onEntityRemoved(const Entity& entity) override {
        if (entityToComponent_.contains(entity.id())) remove(entity);
      }

    private:
      std::vector<C> components_{};
      std::unordered_map<Entity::ID, size_t> entityToComponent_{};
      std::unordered_map<size_t, Entity::ID> componentToEntity_{}; // for removing entity data
    };
  public:
    ECSManager();
    ~ECSManager();

    void addEntity(const Entity& entity);
    // Maybe automate with Shared<>
    void removeEntity(const Entity& entity);

    void onEntityBitsetMutated(const Entity& entity);

    template<class C>
    void registerComponent() {
      FF_ASSERT_E(!componentMaps_.contains(Component<C>::id()), "Attempted duplicate component registration.");
      FF_ASSERT_E(ComponentBase::componentCount() <= ComponentBase::maxComponents, "Maximum component count reached.");
      componentMaps_.insert(std::make_pair(Component<C>::id(), makeShared<ComponentMap<C>>()));
    }

    template<class C>
    void addComponent(const Entity& entity, C component) {
      if (!componentMaps_.contains(Component<C>::id())) registerComponent<C>();
      staticComponentMap<C>()->add(entity, std::move(component));
      bitSetMap_[entity.id()].set(Component<C>::id());
      onEntityBitsetMutated(entity);
    }

    template<class C>
    void removeComponent(const Entity& entity) {
      FF_ASSERT_E(componentMaps_.contains(Component<C>::id()), "Attempted removal of unregistered component.");
      staticComponentMap<C>()->remove(entity);
      bitSetMap_[entity.id()].reset(Component<C>::id());
      onEntityBitsetMutated(entity);
    }

    template<class C>
    C& component(const Entity& entity) {
      FF_ASSERT_E(componentMaps_.contains(Component<C>::id()), "Attempted access of unregistered component.");
      return staticComponentMap<C>()->data(entity);
    }

    [[nodiscard]] const Entity::BitSet& components(const Entity& entity) const {
      return bitSetMap_.at(entity.id());
    }

    template<Derived<SystemBase> S>
    void registerSystem() {
      std::string name{typeid(S).name()};
      FF_ASSERT_E(!systems_.contains(name), "Attempted duplicate system registration.");
      systems_.insert({name, makeShared<S>()});
    }

    void executeSystems() {
      for (auto& [id, system] : systems_) {
        system->onUpdate();
      }
    }

  private:
    boost::unordered_map<Entity::ID, Entity::BitSet> bitSetMap_{};
    std::unordered_map<ComponentBase::ID, Shared<ComponentMapBase>> componentMaps_{};
    std::unordered_map<std::string, Shared<SystemBase>> systems_{};

    template<class C>
    Shared<ComponentMap<C>> staticComponentMap() {
      FF_ASSERT_E(componentMaps_.contains(Component<C>::id()), "Attempted access of unregistered component.");
      return std::static_pointer_cast<ComponentMap<C>>(componentMaps_[Component<C>::id()]);
    };
  };

  template<class C>
  Entity& Entity::addComponent(C component) {
    ecsManager_->template addComponent<C>(*this, std::move(component));
    return *this;
  }

  template<class C>
  Entity& Entity::removeComponent() {
    ecsManager_->template removeComponent<C>(*this);
    return *this;
  }

  template<class C>
  C& Entity::component() {
    return ecsManager_->template component<C>(*this);
  }
}

