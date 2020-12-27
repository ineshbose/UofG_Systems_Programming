#include <stdio.h>
#include <vector>
#include <thread>
#include <mutex>
#include <optional>

struct stack {
private:
  std::vector<int> stack;
  std::mutex mutex;

public:
  void push(int value) {
    std::unique_lock<std::mutex> lock(mutex);
    stack.push_back(value);
  }

  std::optional<int> pop() {
    std::unique_lock<std::mutex> lock(mutex);
    auto v = stack.back();
    stack.pop_back();
    return v; 
  }

};

int main() {
                           // Create and populate a stack
  auto s = stack{};
  s.push(5);
  s.push(10);
  s.push(15);
  s.push(20);

  auto t1 = std::thread([s_ptr = &s]{
      printf("Popped %d\n", s_ptr->pop().value());
  });
  auto t2 = std::thread([s_ptr = &s]{
      printf("Popped %d\n", s_ptr->pop().value());
  });
  s.push(20);
  s.push(25);
  t1.join(); t2.join();

                           // Print the contents of the stack
  printf("\nStack Contains \n");
  for (int i = 0; i < 4; ++i) 
    printf(" -> %d", s.pop().value());
  printf("\n");

}
