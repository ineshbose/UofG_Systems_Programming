#include <stdio.h>
#include <thread>
#include <vector>

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
    std::vector<std::thread> vt;
    for(int i=30;i<40;i++){
        vt.push_back(std::thread([i](){
            printf("fib(%d): %d\n", i, fib(i));
        }));
    }
    for(int i=0; i<vt.size(); i++){
        vt[i].join();
    }
    return 0;
}