#include <functional>
#include <queue>
#include <utility>
#include <vector>
#include "chrono"
#include "ctime"
#include "thread_pool.h"

class TaskWithTimeToExecute {
 public:
  TaskWithTimeToExecute(std::function<void()> func, size_t time_out);
  std::function<void()> first;
  size_t second;
};

class Timer {
 public:
  Timer();
  ~Timer();
  void SetDelayedTask(std::function<void()> task, int delay_millisecond);
  void SleepTo(size_t to);
  void WaitTillEnd();

 private:
  size_t GetCurrentTimeInMilliSeconds();
  void Run();
  std::vector<std::priority_queue<TaskWithTimeToExecute>>* clock_;
  std::vector<std::mutex>* clock_locker_;
  size_t benchmark_;
  ThreadPool* thread_pool_;
  int buckets_, round;
};