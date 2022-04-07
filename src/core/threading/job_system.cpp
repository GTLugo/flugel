//
// Created by galex on 3/24/2022.
//

#include "job_system.hpp"

#include <utility>

namespace ff {

  void JobSystem::init() {
    if (instance_) return;
    Log::trace_e("Initializing Job System...");
    instance_ = new JobSystem{};
    for (size_t i{0}; i < instance_->workerThreadCount_; ++i) {
      instance_->workers_.emplace_back(FF_LAMBDA_INS(JobSystem::workerLoop, instance_));
    }
  }

  void JobSystem::shutdown() {
    for (auto&& worker : instance_->workers_) {
      worker.request_stop();
    }
    delete instance_;
  }

  void JobSystem::kickJob(Job* job) {
    instance_->jobs_.push(job);
  }

  void JobSystem::kickJob(const std::vector<Job*>& jobs) {
    for (auto&& job : jobs) {
      kickJob(job);
    }
  }

  void JobSystem::workerLoop(const std::stop_token& stopToken) {
    while (!stopToken.stop_requested()) {
      auto currentJob{jobs_.pop()};
      if (currentJob.has_value()) {
        currentJob.value()->execute();
        currentJob.value()->contract.setValue();
      } else {
        std::this_thread::sleep_for(MilliSeconds{0.5f});
      }
    }
  }
}