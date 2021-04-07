#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>
#include <thread>

class ThreadPool {
 public:
  void ThreadRunningSequence();
  void PostTask(std::function<void()>);
  void JoinAllThreads();
  void AutoResizeThreadPool(int queued_task);
  ThreadPool(int num = 0);
  ~ThreadPool();

 private:
  std::atomic<bool> auto_resize_;
  int threads_number_, maximum_threads_number_, minimum_threads_number_,
      auto_resize_payload_;
  std::mutex tasks_mutex_, tasks_invoker_, threads_mutex_;
  std::condition_variable tasks_available_;
  std::list<std::thread*> pooled_threads_;
  std::list<std::function<void()>>* tasks_;
};