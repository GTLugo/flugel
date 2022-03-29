//
// Created by galex on 3/25/2022.
//
// Source: https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/

#pragma once

namespace ff {
  // Fixed size very simple thread safe ring buffer
  template<typename T, size_t capacity>
  class ConcurrentRingBuffer {
  public:
    // Push an item to the end if there is free space
    //  Returns true if succesful
    //  Returns false if there is not enough space
    inline bool push_back(const T& item) {
      bool result = false;
      std::lock_guard<std::mutex> lock{mutex_};
      size_t next = (head_ + 1) % capacity;
      if (next != tail_) {
        data_[head_] = item;
        head_ = next;
        result = true;
      }
      return result;
    }

    // Get an item if there are any
    //  Returns true if succesful
    //  Returns false if there are no items
    inline bool pop_front(T& item) {
      bool result = false;
      std::lock_guard<std::mutex> lock{mutex_};
      if (tail_ != head_) {
        item = data_[tail_];
        tail_ = (tail_ + 1) % capacity;
        result = true;
      }
      return result;
    }

  private:
    T data_[capacity];
    size_t head_ = 0;
    size_t tail_ = 0;
    std::mutex mutex_; // this just works better than a spinlock here (on windows)
  };
}

