// https://stackoverflow.com/a/32593825/17004103
#pragma once

namespace fge {
  class FGE_API ThreadPool {
    using JobFn = std::function<void()>;
  public:
    ThreadPool(uint32_t numThreads = std::thread::hardware_concurrency());
    ~ThreadPool();

    void pushJob(const JobFn& job);
  private:
    std::vector<std::thread> threadPool_{};
    std::queue<JobFn> jobQueue_{};

    std::condition_variable queueCondition_; 
    std::mutex queueMutex_;
    std::mutex threadPoolMutex_;

    bool killPool{false};
    
    void initialize(uint32_t numThreads);
    void shutdown();

    void threadLoop();
  };
}