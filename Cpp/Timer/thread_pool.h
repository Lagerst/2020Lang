#include <functional>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

class ThreadPool {
 public:
  void ThreadRunningSequence();
  void PostTask(std::function<void()>);
  void JoinAllThreads();
  ThreadPool(int num);
  ~ThreadPool();

 private:
  bool auto_resize_ = false;
  int thread_number_ = 0;
  std::mutex tasks_mutex_, tasks_invoker_;
  std::condition_variable tasks_available_;
  std::list<std::thread*> pooled_threads_;
  std::list<std::function<void()>>* tasks_;
};