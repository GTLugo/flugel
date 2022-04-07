//
// Created by galex on 3/24/2022.
//
// Sources:
// https://blog.molecular-matters.com/2015/08/24/job-system-2-0-lock-free-work-stealing-part-1-basics/
// https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/
// https://benhoffman.tech/cpp/general/2018/11/13/cpp-job-system.html

#pragma once

#include "concurrent_queue.hpp"
//#include "concurrent_ring_buffer.hpp"
//#include <boost/fiber/all.hpp>

namespace ff {
  struct JobContract {
    explicit JobContract() : promise_{}, future_{promise_.get_future()} {}
    //~JobContract() { delete promise_; }

    void setValue() { promise_.set_value(); }
    void wait() { return future_.get(); }
  private:
    std::promise<void> promise_;
    std::future<void> future_;
  };

  struct Job {
    friend class JobSystem;

    virtual ~Job() = default;
    void wait() { return contract.wait(); }
    virtual void execute() = 0;
  private:
    JobContract contract{};
  };

  class JobSystem {
  public:
    static void init();
    static void shutdown();

    static void kickJob(Job* job);
    static void kickJob(const std::vector<Job*>& jobs);

    static size_t workerCount() { return instance_->workerThreadCount_; }

    JobSystem(const JobSystem& other) = delete;
    JobSystem& operator=(const JobSystem& other) = delete;
  private:
    static inline JobSystem* instance_{nullptr};

    const size_t hardwareThreadCount_{std::thread::hardware_concurrency()};
    const size_t workerThreadCount_{hardwareThreadCount_ - 2};

    JobSystem() = default;
    ~JobSystem() = default;

    ConcurrentQueue<Job*> jobs_{};
    std::vector<std::jthread> workers_{};

    void workerLoop(const std::stop_token& stopToken);
  };
}
