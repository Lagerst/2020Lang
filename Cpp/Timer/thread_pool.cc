#include "thread_pool.h"
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

#define Min(a, b) (a < b) ? a : b

ThreadPool::ThreadPool(int num) {
  maximum_threads_number_ = 5;
  minimum_threads_number_ = 2;
  auto_resize_payload_ = 1;
  int threads_number;
  if (num <= 0) {
    auto_resize_ = true;
    threads_number = minimum_threads_number_;
  } else {
    threads_number = num;
  }
  std::cout << "Thread pool number set to " << threads_number << "."
            << std::endl;
  tasks_ = new std::list<std::function<void()>>();
  for (int i = 0; i < threads_number; ++i) {
    std::thread* t = new std::thread(&ThreadPool::ThreadRunningSequence, this);
    pooled_threads_.push_back(t);
  }
}

ThreadPool::~ThreadPool() = default;

void ThreadPool::ThreadRunningSequence() {
  std::function<void()> first_task;
  int queued_task;
  while (true) {
    {
      tasks_mutex_.lock();
      if (tasks_->empty()) {
        tasks_mutex_.unlock();
        std::unique_lock<std::mutex> locker(tasks_invoker_);
        tasks_available_.wait(locker);
        continue;
      }
      first_task = *tasks_->begin();
      tasks_->pop_front();
      queued_task = tasks_->size();
      tasks_mutex_.unlock();
    }
    if (auto_resize_) {
      AutoResizeThreadPool(queued_task);
    }
    first_task();
  }
}

void ThreadPool::AutoResizeThreadPool(int queued_task) {
  size_t suggested_num =
      Min(queued_task / auto_resize_payload_, maximum_threads_number_);
  if (suggested_num > pooled_threads_.size() && threads_mutex_.try_lock()) {
    while (suggested_num > pooled_threads_.size()) {
      std::thread* t =
          new std::thread(&ThreadPool::ThreadRunningSequence, this);
      pooled_threads_.push_back(t);
      std::cout << "Thread pool number set to " << pooled_threads_.size() << "."
                << std::endl;
    }
    threads_mutex_.unlock();
  }
}

void ThreadPool::PostTask(std::function<void()> task) {
  std::lock_guard<std::mutex> locker_var_(tasks_mutex_);
  tasks_->push_back(task);
  tasks_available_.notify_one();
}

void ThreadPool::JoinAllThreads() {
  for (auto thread : pooled_threads_) {
    thread->join();
  }
}