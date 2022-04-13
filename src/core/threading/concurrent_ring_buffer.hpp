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
    class Iterator {
      using iterator_category = std::forward_iterator_tag;
      using value_type = T;
      using difference_type = T;
      using pointer = T*;
      using reference = T&;
    public:
      Iterator(pointer x) : p(x) {}
      Iterator(const Iterator& mit) : p(mit.p) {}
      Iterator& operator++() {
        ++p;
        return *this;
      }
      Iterator operator++(value_type) {
        Iterator tmp(*this);
        operator++();
        return tmp;
      }
      bool operator==(const Iterator& rhs) const { return p == rhs.p; }
      bool operator!=(const Iterator& rhs) const { return p != rhs.p; }
      reference operator*() {return *p;}
    private:
      pointer p;
    };

    // Push an item to the end if there is free space
    //  Returns true if successful
    //  Returns false if there is not enough space
    bool push(const T& item) {
      bool result{false};
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
    //  Returns value if successful
    //  Returns empty if there are no items
    std::optional<T> pop() {
      std::lock_guard<std::mutex> lock{mutex_};
      if (tail_ == head_) {
        return {};
      }
      T item = data_[tail_];
      tail_ = (tail_ + 1) % capacity;;
      return item;
    }

    Iterator begin() { return Iterator{head_}; }
    Iterator end() { return Iterator{tail_}; }

  private:
    T data_[capacity];
    size_t head_ = 0;
    size_t tail_ = 0;
    std::mutex mutex_; // this just works better than a spinlock here (on windows)
  };
}

