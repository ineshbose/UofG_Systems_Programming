# Lab 6

## Creating & Waiting for Threads

### Sequential Three Fibs
Write a C++ program `three_fibs.cpp` that prints out the values of Fibonacci(40), Fibonacci(41), and Fibonacci(42).

### Threaded Three Fibs
Refactor the above program into `three_fibs_threaded.cpp` to create two threads, one to print out Fibonacci(40), and the other to print Fibonacci(41) while `main()` prints Fibonacci(42).

### Performance Analysis
Use `time` to record the (real) execution time for at least three runs of `three_fibs` and `three_fibs_threaded`, eg
```sh
    $ time ./three_fibs
```


## Creating an Array of Threads, Capturing Values

### Array of Threads Program
Write a C++ program `ten_fibs.cpp` that creates an `std::vector` of threads, and uses them to compute Fibonacci(30)..Fibonacci(39).


## Making a Thread Safe Data Structure

### A Thread Safe Stack
Make the extremely simple stack data structure in `stack.cpp` thread safe: `safe_stack.cpp`.

### Testing the Safe Stack
Create at least two threads to operate on the stack concurrently. Run the program several times to check for race conditions.