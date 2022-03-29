//
// Created by galex on 3/24/2022.
//

#include "job_system.hpp"

#include <utility>

namespace ff {
  /*
  JobManager::JobManager()
      : completed_{false} {
    const u32 supportedThreads{static_cast<u32>(hardwareSupportedThreadCount()) - 2};
    Log::debug_e("Supported thread count: ", supportedThreads);
    for (size_t i{0}; i < supportedThreads; ++i) {
      workers_.emplace_back(&JobManager::workerThread, this);
    }
  }

  JobManager::~JobManager() {
    completed_ = true;
    for (auto& w : workers_) {
      w.join();
    }
  }

  void JobManager::pushJob(Job::Function action, void* data, i32 index) {
    pushJob({std::move(action), data, index});
  }

  void JobManager::pushJob(const JobManager::Job& job) {
    jobQueue_.push(job);
  }

  void JobManager::workerThread() {
    while (!completed_) {
      auto currentJob{jobQueue_.pop()};
      if (currentJob.has_value()) {
        currentJob.value().invoke();
      } else {
        std::this_thread::sleep_for(MilliSeconds{1});
      }
    }
  }
  */


  void JobSystem::init() {
    if (instance_) return;
    instance_ = new JobSystem{};
    for (size_t i{0}; i < instance_->workerThreadCount_; ++i) {
      instance_->workers_.emplace_back(&JobSystem::workerThread, instance_);
    }
  }

  void JobSystem::shutdown() {
    instance_->killSystem_ = true;
    for (auto&& worker : instance_->workers_) {
      worker.join();
    }
    delete instance_;
  }

  void JobSystem::kickJob(const Job& job) {
    instance_->jobs_.push(job);
  }

  void JobSystem::kickJob(const std::vector<Job>& jobs) {
    for (auto&& job : jobs) {
      kickJob(job);
    }
  }

  void JobSystem::workerThread() {
    while (!killSystem_) {
      auto currentJob{jobs_.pop()};
      if (currentJob.has_value()) {
        currentJob.value().contract->setValue(currentJob.value().function(currentJob.value().data));
      } else {
        std::this_thread::sleep_for(MilliSeconds{0.5f});
      }
    }
  }
}