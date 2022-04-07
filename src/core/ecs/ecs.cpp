//
// Created by galex on 3/31/2022.
//

#include "ecs.hpp"

namespace ff {
  Entity::Entity(ECSManager* ecs)
    : ecsManager_{ecs} {
    Log::debug_e(R"(Creating entity "{}")", id_);
    ecsManager_->registerEntity(*this);
  }

  Entity::~Entity() {
    // kill();
  }

  void Entity::kill() {
    Log::debug_e(R"(Removing entity "{}")", id_);
    ecsManager_->removeEntity(*this);
  }

  const Entity::BitSet& Entity::components() const {
    //return bitSet_;
    return ecsManager_->components(*this);
  }

  void ECSManager::removeEntity(Entity& entity) {
    for (auto&& [id, componentMap] : componentMaps_) {
      componentMap->onEntityRemoved(entity);
    }
    //bitSetMap_.erase(entity.id());
  }

  void ECSManager::onEntityBitsetMutated(Entity& entity)  {
    for (auto& [id, system] : systems_) {
      if (FF_BIT_COMPARE_TO(entity.components(), system->components())) {
        system->entities.push_back(entity);
      } else {
        auto itr{std::find(system->entities.begin(), system->entities.end(), entity)};
        if (itr != system->entities.end()) system->entities.erase(itr);
      }
    }
  }
}