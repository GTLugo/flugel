//
// Created by galex on 3/25/2022.
//
// Implemented from https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue/

#pragma once

namespace ff {
  template<class T>
  class ConcurrentQueue {
  public:
    ConcurrentQueue() = default;
    ConcurrentQueue(ConcurrentQueue<T>&& other) noexcept {
      std::lock_guard<std::mutex> lock{mutex_};
      queue_ = std::move(other.queue_);
    }

    virtual ~ConcurrentQueue() = default;

    size_t size() const {
      std::lock_guard<std::mutex> lock{mutex_};
      return queue_.size();
    }

    std::optional<T> pop() {
      std::lock_guard<std::mutex> lock{mutex_};
      if (empty()) {
        return {};
      }
      T tmp{queue_.front()};
      queue_.pop();
      return tmp;
    }

    void push(const T& element) {
      std::lock_guard<std::mutex> lock{mutex_};
      queue_.push(element);
    }

    ConcurrentQueue(const ConcurrentQueue<T>&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue<T>&) = delete;
  private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;


    // apparently this can cause a race condition between this and pop(),
    // which is why this isn't public. Emptiness should be tested via pop,
    // which shall return an empty optional when the queue is empty
    [[nodiscard]] bool empty() const {
      return queue_.empty();
    }
  };
}

