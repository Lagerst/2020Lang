#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>

std::list<int> some_list;
std::mutex value_mutex;

void add_to_list(int new_value) {
  std::lock_guard<std::mutex> mutex(value_mutex);
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
  std::lock_guard<std::mutex> mutex(value_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) !=
         some_list.end();
}

int main() {
  add_to_list(33);
  std::cout << "contains(1)=" << list_contains(1)
            << ",contains(33)=" << list_contains(33) << std::endl;
  return 0;
}