// https://stackoverflow.com/a/32593825/17004103
#pragma once

namespace fge {
  class FGE_API ThreadPool {
    using JobFn = std::function<void()>;
  public:
    ThreadPool() = default;
    ~ThreadPool() = default;
    
    void initialize(uint32_t numThreads = std::thread::hardware_concurrency());
    void shutdown();

    void pushJob(const JobFn& job);
  private:
    std::vector<std::thread> threadPool_{};
    std::queue<JobFn> jobQueue_{};

    std::condition_variable queueCondition_; 
    std::mutex queueMutex_;
    std::mutex threadPoolMutex_;

    bool killPool{false};

    void threadLoop();
  };
}