//
// Created by galex on 3/24/2022.
//
// Sources:
// https://blog.molecular-matters.com/2015/08/24/job-system-2-0-lock-free-work-stealing-part-1-basics/
// https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/
// https://benhoffman.tech/cpp/general/2018/11/13/cpp-job-system.html
// https://dens.website/articles/cpp-threadpool

#pragma once

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
//#include <boost/fiber/all.hpp>

namespace ff {
  struct JobContract {
    explicit JobContract(): promise{}, future{promise.get_future()} {}

    std::promise<void> promise;
    std::future<void> future;
  };

  struct Job {
    friend class JobSystem;

    virtual ~Job() = default;

    void wait() {
      try {
        return contract.future.wait();
      } catch (const std::exception& e) {
        Log::error_e(e.what());
      }
    }

    virtual void execute() = 0;
  private:
    JobContract contract{};
  };

  class JobSystem {
  public:
    static void init();
    static void shutdown();

    static void submit(const Shared<Job>& job);
    static void submit(const std::vector<Shared<Job>>& jobs);

    static size_t workerCount() { return instance_->workerThreadCount_; }

    JobSystem(const JobSystem& other) = delete;
    JobSystem& operator=(const JobSystem& other) = delete;
  private:
    static inline JobSystem* instance_{nullptr};

    const size_t hardwareThreadCount_{std::thread::hardware_concurrency()};
    const size_t workerThreadCount_{hardwareThreadCount_ - 2};

    JobSystem() = default;
    ~JobSystem() = default;

    Unique<boost::asio::thread_pool> workers_;
  };
}
