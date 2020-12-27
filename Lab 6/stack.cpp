#include <stdio.h>
#include <vector>
#include <optional>

//  An extremely simple stack data structure (e.g. no test for empty!)
//  Directly uses an std::vector 
//  Phil Trinder, November 2020 

struct stack {
private:
  std::vector<int> stack;

public:
  void push(int value) {
    stack.push_back(value);
  }

  std::optional<int> pop() {
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

  printf("Popped %d\n", s.pop().value());
  s.push(20);
  s.push(25);
  printf("Popped %d\n", s.pop().value());

                           // Print the contents of the stack
  printf("\nStack Contains \n");
  for (int i = 0; i < 4; ++i) 
    printf(" -> %d", s.pop().value());
  printf("\n");

}
