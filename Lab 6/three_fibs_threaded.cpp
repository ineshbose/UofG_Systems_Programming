#include <stdio.h>
#include <thread>

int fib(int x, int x1, int x2) {
    if (x == 0) {
        return x2;
    } else {
        return fib(x - 1, x1 + x2, x1);
    }
}

int fib(int x) {
    return fib(x, 0, 1);
}

int main(){
    auto t1 = std::thread([]{
        printf("40: %d\n", fib(40));
    });
    auto t2 = std::thread([]{
        printf("41: %d\n", fib(41));
    });
    printf("42: %d\n", fib(42));
    t1.join();
    t2.join();
    return 0;
}