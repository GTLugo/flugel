//
// Created by galex on 3/31/2022.
//

#include "ecs.hpp"

namespace ff {
  Entity::Entity(ECSManager* ecs)
    : ecsManager_{ecs} {
    ecsManager_->addEntity(*this);
  }

  Entity::~Entity() {
    //ecsManager_->removeEntity(*this);
  }

  const Entity::BitSet& Entity::components() const {
    return ecsManager_->components(*this);
  }

  ECSManager::ECSManager() {

  }

  ECSManager::~ECSManager() {

  }

  void ECSManager::addEntity(const Entity& entity) {
    //return Entity{};
  }

  void ECSManager::removeEntity(const Entity& entity) {
    for (auto&& [id, componentMap] : componentMaps_) {
      componentMap->onEntityRemoved(entity);
    }
    bitSetMap_.erase(entity.id());
  }

  void ECSManager::onEntityBitsetMutated(const Entity& entity)  {
    for (auto& [id, system] : systems_) {
      if (FF_BIT_COMPARE_TO(entity.components(), system->components())) {
        system->entities.insert({entity.id(), entity});
      } else {
        system->entities.erase(entity.id());
      }
    }
  }
}