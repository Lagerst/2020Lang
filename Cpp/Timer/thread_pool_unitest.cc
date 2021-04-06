#include <functional>
#include <mutex>
#include "iostream"
#include "thread_pool.h"
#include "unistd.h"

std::mutex p;
int x;
void Test() {
  std::lock_guard<std::mutex> t(p);
  std::cout << "ExecutedXXX: " << ++x << std::endl;
}

int main() {
  std::cout << "Thread pool unitest start." << std::endl;
  ThreadPool* t = new ThreadPool(3);
  for (int i = 0; i < 10; ++i)
    t->PostTask(std::bind(&Test));
  t->JoinAllThread();
}