//
// Created by galex on 3/24/2022.
//

#include "job_system.hpp"

namespace ff {
  void JobManager::init() {
    if (instance_) return;
    Log::trace_e("Initializing Job System...");
    instance_ = new JobManager{};
    instance_->workers_ = makeUnique<boost::asio::thread_pool>(workerCount());
  }

  void JobManager::shutdown() {
    Log::trace_e("Shutting down Job System...");
    instance_->workers_->stop();
    delete instance_;
    Log::trace_e("Job System shut down.");
  }

  void JobManager::submit(const Shared<Job>& job) {
    boost::asio::post(*instance_->workers_, [=]{
      try {
        job->execute();
        job->contract.promise.set_value();
      } catch (std::exception&) {
        job->contract.promise.set_exception(std::current_exception());
      }
    });
  }

  void JobManager::submit(const std::vector<Shared < Job>>& jobs) {
    for (auto&& job : jobs) {
      boost::asio::post(*instance_->workers_, [=]{
        try {
          job->execute();
          job->contract.promise.set_value();
        } catch (std::exception&) {
          job->contract.promise.set_exception(std::current_exception());
        }
      });
    }
  }
}