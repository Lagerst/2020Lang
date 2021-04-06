#include "timer.h"
#include "iostream"

std::mutex p;
int x;
void Test() {
  std::lock_guard<std::mutex> t(p);
  std::cout << "ExecutedXXX: " << ++x << std::endl;
}

int main() {
    Timer* t = new Timer();
    for (int i = 0; i < 10; ++i)
        t->SetDelayedTask(std::bind(&Test), 500 * (i + 3));
    t->WaitTillEnd();
}