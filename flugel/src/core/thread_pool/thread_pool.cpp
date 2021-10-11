#include "thread_pool.hpp"

namespace fge {
  ThreadPool::ThreadPool(uint32_t numThreads) {
    initialize(numThreads);
    FGE_TRACE_ENG("Thread pool size: {0}", threadPool_.size());
  }

  ThreadPool::~ThreadPool() {
    shutdown();
  }

  void ThreadPool::threadLoop() {
    while (!killPool) {
      JobFn job;
      { // Mutex lock scope
        std::unique_lock<std::mutex> lock{queueMutex_};
        queueCondition_.wait(lock, [this]{
          return !jobQueue_.empty() || killPool;
        });

        if (!jobQueue_.empty()) {
          job = jobQueue_.front();
          jobQueue_.pop();
        }
      } // Unlock mutex

      if (job != nullptr) {
        FGE_TRACE_ENG("Starting job on thread: {0}", std::this_thread::get_id());
        job();
      }
    }
  }
   
  void ThreadPool::initialize(uint32_t numThreads) {
    FGE_TRACE_ENG("Initializing thread pool...");
    for (uint32_t i = 0; i < numThreads; ++i) {
      threadPool_.push_back(std::thread{FGE_BIND(threadLoop)});
    }
  }
   
  void ThreadPool::shutdown() {
    FGE_TRACE_ENG("Shutting down thread pool...");
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{threadPoolMutex_};
      killPool = true;
    } // Unlock mutex

    queueCondition_.notify_all(); // wake up threads;

    FGE_TRACE_ENG("Joining threads...");
    for (auto& thread : threadPool_) {
      thread.join();
    }

    threadPool_.clear();
  }

  void ThreadPool::pushJob(const JobFn& job) {
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{threadPoolMutex_};
      jobQueue_.push(job);
    } // Unlock mutex

    queueCondition_.notify_one();
  }
}