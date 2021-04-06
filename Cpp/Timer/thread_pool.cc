#include "thread_pool.h"
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

ThreadPool::ThreadPool(int num) {
  if (num <= 0) {
    auto_resize_ = true;
    thread_number_ = 1;
  } else {
    thread_number_ = num;
  }
  std::cout << "Thread pool num set to " << thread_number_ << "." << std::endl;
  for (int i = 0; i < thread_number_; ++i) {
    std::cout << "Main thread try to launch thread " << i << "." << std::endl;
    std::thread* t = new std::thread(&ThreadPool::ThreadRunningSequence, this);
    pooled_threads_.push_back(t);
  }
}

ThreadPool::~ThreadPool() = default;

void ThreadPool::ThreadRunningSequence() {
  std::cout << "A new thread start.\n";
  std::function<void()> first_task;
  while (true) {
    {
      std::lock_guard<std::mutex> locker_var_(tasks_mutex_);
      if (tasks_.empty()) {
        std::unique_lock<std::mutex> locker(tasks_invoker_);
        tasks_available_.wait(locker);
      }
      first_task = std::move(*tasks_.begin());
      tasks_.pop_front();
    }
    std::cout << "A task is executed." << std::endl;
    first_task();
  }
}

void ThreadPool::PostTask(std::function<void()> task) {
  std::lock_guard<std::mutex> locker_var_(tasks_mutex_);
  std::cout << "A task is pushed to queue." << std::endl;
  tasks_.push_back(task);
  tasks_available_.notify_one();
}

void ThreadPool::JoinAllThread() {
  for (auto thread : pooled_threads_) {
    thread->join();
  }
}