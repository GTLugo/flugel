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
  /*
  class JobManager {
    struct Job {
      using Function = std::function<void(void* args, i32 aIndex)>;

      bool invoke() {
        try {
          funcPtr(data, index);
          return true;
        } catch (const std::bad_function_call& e) {
          Log::error_e(e.what());
          return false;
        }
      }

      Function funcPtr{};
      void* data{nullptr};
      i32 index{0};
    };
  public:
    static JobManager& instance() {
      if (instance_ == nullptr) {
        instance_ = new JobManager();
      }
      return *instance_;
    }

    static void releaseInstance() {
      if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
      }
    }

    void pushJob(Job::Function action, void* data = nullptr, i32 index = 0);
    void pushJob(const Job& job);

    size_t workerThreadCount() { return workers_.size(); }
    static size_t hardwareSupportedThreadCount() { return std::thread::hardware_concurrency(); }

    JobManager(JobManager const&) = delete;
    void operator=(JobManager const&) = delete;
  private:
    static inline JobManager* instance_{nullptr};

    ConcurrentQueue<Job> jobQueue_;
    std::vector<std::thread> workers_;
    std::atomic<bool> completed_;

    JobManager();
    ~JobManager();

    void workerThread();
  };
  */

  struct Counter {

  };

//  JobContract jobContract{};
//  JobSystem::kickJob({
//    .contract = &jobContract,
//    .function = [this](void*) -> void* {
//      return {};
//    }
//  });
//  auto result{jobContract.wait()};

  struct JobContract {
    explicit JobContract() : promise_{}, future_{promise_.get_future()} {}
    //~JobContract() { delete promise_; }

    void setValue(void* value) { promise_.set_value(value); }
    void* wait() { return future_.get(); }
  private:
    std::promise<void*> promise_;
    std::future<void*> future_;
  };

  struct Job {
    using Function = std::function<void*(void* data)>;

    //enum class Priority {
    //  LOW, NORMAL, HIGH,
    //};

    //Priority priority{Priority::NORMAL};
    JobContract* contract{nullptr};
    Function function;
    void* data{nullptr};
    //Counter counter{};
  };

  class JobSystem {
  public:
    //static JobSystem& instance() { return *instance_; }

    static void init();
    static void shutdown();

    static void kickJob(const Job& job);
    static void kickJob(const std::vector<Job>& jobs);

    JobSystem(const JobSystem& other) = delete;
    JobSystem& operator=(const JobSystem& other) = delete;
  private:
    static inline JobSystem* instance_{nullptr};

    bool killSystem_{false};
    const u32 hardwareThreadCount_{std::thread::hardware_concurrency()};
    const u32 workerThreadCount_{hardwareThreadCount_ - 2};

    JobSystem() = default;
    ~JobSystem() = default;

    ConcurrentQueue<Job> jobs_{};
    std::vector<std::thread> workers_{};

    void workerThread();
  };
}
