#include "thread_pool.hpp"

namespace ff {
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
        Log::trace_e("Starting job on thread: {0}", std::this_thread::get_id());
        job();
      }
    }
  }
   
  void ThreadPool::initialize(u32 numThreads) {
    for (u32 i = 0; i < numThreads; ++i) {
      threadPool_.emplace_back(FF_BIND_AS_LAMBDA(threadLoop));
    }
    Log::debug_e("Initialized thread pool! Number of threads: {0}", threadPool_.size());
  }
   
  void ThreadPool::shutdown() {
    Log::trace_e("Shutting down thread pool...");
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{threadPoolMutex_};
      killPool = true;
    } // Unlock mutex

    queueCondition_.notify_all(); // wake up threads;

    Log::trace_e("Joining threads...");
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