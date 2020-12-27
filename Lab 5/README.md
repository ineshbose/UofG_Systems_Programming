# Lab 5


## Exercise 1

### Pthreads "Hello World" Program
Create a simple Pthreads program that does the following:
* Includes the `pthread.h` header file
* Main program creates several threads each of which executes a "print hello" thread routine. The argument passed to that routine is their thread ID.
* The thread's "print hello" routine accepts the thread ID argument and prints "hello world from thread #". Then it calls `pthread_exit` to finish.
* Main program calls `pthread_exit` as the last thing it does.

### Thread Scheduling
Review the example code [`hello32.c`](https://computing.llnl.gov/tutorials/pthreads/samples/hello32.c). A `sleep();` statement has been introduced to help insure that all threads will be in existence at the same time. Also, each thread performs actual work to demonstrate how the OS scheduler behaviour determines the order of thread completion.

### Argument Passing
Review the [`hello_arg1.c`](https://computing.llnl.gov/tutorials/pthreads/samples/hello_arg1.c) and [`hello_arg2.c`](https://computing.llnl.gov/tutorials/pthreads/samples/hello_arg2.c) example codes. Notice how the single argument is passed and how to pass multiple arguments through a structure. Compile and run both programs. Do the same with [`bug3.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug3.c). Make changes if required.

### Thread Exiting
Review, compile and run the [`bug5.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug5.c) program. Make changes if required.

### Thread Joining
Review, compile and run the [`join.c`](https://computing.llnl.gov/tutorials/pthreads/samples/join.c) program. Modify the program so that threads send back a different return code. For comparison, review, compile and run the [`detached.c`](https://computing.llnl.gov/tutorials/pthreads/samples/detached.c) example code.

### Stack Management
Review, compile and run the [`bug2.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug2.c) program. Make changes if required and try out [`bug2fix.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug2fix.c) program.


## Exercise 2

### Mutexes
* Review, compile and run the [`dotprod_serial.c`](https://computing.llnl.gov/tutorials/pthreads/samples/dotprod_serial.c) program. As its name implies, it is serial - no threads are created.
* Now review, compile and run the [`dotprod_mutex.c`](https://computing.llnl.gov/tutorials/pthreads/samples/dotprod_mutex.c) program. This version of the dotprod program uses threads and requires a mutex to protect the global sum as each thread updates it with their partial sums.
* Execute the `dotprod_mutex` program several times and notice that the order in which threads update the global sum varies.
* Review, compile and run the [`bug6.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug6.c) program.
* Run it several times and notice what the global sum is each time. An example solution is provided by the [`bug6fix.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug6fix.c) program.
* The [`arrayloops.c`](https://computing.llnl.gov/tutorials/pthreads/samples/arrayloops.c) program is another example of using a mutex to protect updates to a global sum.

### Condition Variables
* Review, compile and run the [`condvar.c`](https://computing.llnl.gov/tutorials/pthreads/samples/condvar.c) program.
* Review, compile and run the [`bug1.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug1.c) program. Observe the output of the five threads. An example solution is provided by the [`bug1fix.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug1fix.c) program.
* The [`bug4.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug4.c) program is yet another example of what can go wrong when using condition variables. Review, compile and run the code. An example solution is provided by the [`bug4fix.c`](https://computing.llnl.gov/tutorials/pthreads/samples/bug4fix.c) program.