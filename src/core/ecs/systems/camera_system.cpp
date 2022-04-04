//
// Created by galex on 4/3/2022.
//

#include "camera_system.hpp"

namespace ff {
  void CameraSystem::onUpdate() {
    for (auto& entity : entities) {
      auto& transform{entity.getRef<Transform>()};
      auto& camera{entity.getRef<Camera>()};
      camera.viewMatrix = glm::inverse(transform.matrix());
    }
  }
}


//    struct SystemJob : ff::Job {
//      std::vector<ff::Entity_> entities{};
//
//      explicit SystemJob(std::vector<ff::Entity_> entities_) : entities{std::move(entities_)} {}
//
//      void execute() override {
//        for (auto& entity : entities) {
//          auto& transform{entity.component<ff::Transform>()};
//          auto& camera{entity.component<ff::Camera>()};
//          camera.viewMatrix = glm::inverse(transform.matrix());
//        }
//      }
//    };

//      std::vector<ff::Job*> jobs{};
//      //size_t count{entities.size()};
//      size_t batch{static_cast<size_t>(glm::ceil(entities.size() / ff::JobSystem::workerCount()))};
//      size_t offset{0};
//
//      auto end{entities.begin()};
//      while (end != entities.end()) {
//        end = (offset + batch < entities.size()) ? end + batch : entities.end();
//        jobs.emplace_back(new SystemJob{{entities.begin() + offset, end}});
//        offset += batch;
//      }
//
//      ff::JobSystem::kickJob(jobs);
//
//      entities.clear();
//      for (auto& job : jobs) {
//        job->wait();
//        auto sysJob{dynamic_cast<SystemJob*>(job)};
//        entities.insert(entities.end(), sysJob->entities.begin(), sysJob->entities.end());
//      }

//      SystemJob job{std::move(entities)};
//      ff::JobSystem::kickJob(&job);
//      job.wait();
//      entities = std::move(job.entities);