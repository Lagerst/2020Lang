#include "timer.h"
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include "iostream"

TaskWithTimeToExecute::TaskWithTimeToExecute(std::function<void()> func,
                                             size_t time_out) {
  task = func;
  execute_time = time_out;
}

bool operator<(const TaskWithTimeToExecute& a, const TaskWithTimeToExecute& b) {
  return a.execute_time > b.execute_time;
}

Timer::Timer() {
  buckets_ = 512;
  clock_ = new std::vector<std::priority_queue<TaskWithTimeToExecute> >(
      buckets_, std::priority_queue<TaskWithTimeToExecute>());
  clock_locker_ = new std::vector<std::mutex>(buckets_);
  benchmark_ = GetCurrentTimeInMilliSeconds();
  round = 0;
  thread_pool_ = new ThreadPool();
  thread_pool_->PostTask(std::bind(&Timer::Run, this));
}

Timer::~Timer() = default;

void Timer::SetDelayedTask(std::function<void()> task,
                           size_t delay_millisecond) {
  size_t current_snapshot =
      GetCurrentTimeInMilliSeconds() + delay_millisecond - benchmark_;
  unsigned char hash = current_snapshot / 1000 % buckets_;
  // std::cout << "Task with delay = " << current_snapshot
  //           << " is put into hash = " << int(hash) << std::endl;
  std::lock_guard<std::mutex> locker((*clock_locker_)[hash]);
  (*clock_)[hash].push(TaskWithTimeToExecute(task, current_snapshot));
}

void Timer::Run() {
  int bucket = 0;
  while (true) {
    {
      std::lock_guard<std::mutex> locker((*clock_locker_)[bucket]);
      while (!(*clock_)[bucket].empty() &&
             (*clock_)[bucket].top().execute_time <=
                 (bucket + round * buckets_ + 1) * 1000) {
        SleepTo((*clock_)[bucket].top().execute_time);
        thread_pool_->PostTask((*clock_)[bucket].top().task);
        (*clock_)[bucket].pop();
      }
    }
    bucket++;
    if (bucket == buckets_) {
      round++;
      bucket = 0;
    }
    SleepTo((bucket + round * buckets_) * 1000);
  }
}

void Timer::SleepTo(size_t wake_time) {
  int time_to_sleep = wake_time - (GetCurrentTimeInMilliSeconds() - benchmark_);
  if (time_to_sleep > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
  }
}

size_t Timer::GetCurrentTimeInMilliSeconds() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::time_point_cast<std::chrono::milliseconds>(
                 std::chrono::high_resolution_clock::now())
                 .time_since_epoch())
      .count();
}

void Timer::WaitTillEnd() {
  thread_pool_->JoinAllThreads();
}