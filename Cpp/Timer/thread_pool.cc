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
  tasks_ = new std::list<std::function<void()>>();
  for (int i = 0; i < thread_number_; ++i) {
    std::thread* t = new std::thread(&ThreadPool::ThreadRunningSequence, this);
    pooled_threads_.push_back(t);
  }
}

ThreadPool::~ThreadPool() = default;

void ThreadPool::ThreadRunningSequence() {
  std::function<void()> first_task;
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
      tasks_mutex_.unlock();
    }
    first_task();
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