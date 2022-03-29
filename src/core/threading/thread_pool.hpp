// https://stackoverflow.com/a/32593825/17004103
#pragma once

namespace ff {
  class ThreadPool {
    using JobFn = std::function<void()>;
  public:
    ThreadPool() = default;
    ~ThreadPool() = default;
    
    void initialize(u32 numThreads = std::thread::hardware_concurrency());
    void shutdown();

    void pushJob(const JobFn& job);
  private:
    std::mutex threadPoolMutex_;
    std::vector<std::thread> threadPool_{};

    std::condition_variable queueCondition_;
    std::mutex queueMutex_;
    std::queue<JobFn> jobQueue_{};

    bool killPool{false};

    void threadLoop();
  };
}