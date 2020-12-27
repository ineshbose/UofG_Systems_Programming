# Coursework 2: Concurrent Dependency Discoverer


## Requirements

Large-scale systems developed in C and C++ tend to include a large number of `.h` files, both of a system variety (enclosed in `< >`) and non-system (enclosed in `“ ”`). The `make` utility and Makefiles are a convenient way to record dependencies between source files, and to minimize the amount of work that is done when the system needs to be rebuilt. Of course, the work will only be minimized if the `Makefile` exactly captures the dependencies between source and object files.

Some systems are extremely large and it is difficult to keep the dependencies in the Makefile correct as many people concurrently make changes. Therefore, there is a need for a program that can crawl over source files, noting any `#include` directives, and recurse through files specified in `#include` directives, and finally generate the correct dependency specifications.

`#include` directives for system files (enclosed in `< >`) are normally NOT specified in dependencies. Therefore, this system will focus on generating dependencies between source files and non-system `#include` directives (enclosed in `“ ”`).

For very large software systems, a singly-threaded application to crawl the source files may take a very long time. The purpose of this assessed exercise is to develop a concurrent include file crawler in C++.


## Specification

Create a C++17 program `dependencyDiscoverer.cpp` based on a sequential template. The `main()` function must understand the following arguments:

```
    -Idir       indicates a directory to be searched for any include files encountered
    file.ext    source file to be scanned for #include directives; ext must be c, y, or l
```

The usage string is `./dependencyDiscoverer [-Idir] file1.ext [file2.ext ...]`

The application uses the following environment variables when it runs:
* `CRAWLER_THREADS`: if this is defined, it specifies the number of worker threads that the application must create; if it is not defined, then two (2) worker threads should be created.
* `CPATH`: if this is defined, it contains a list of directories separated by `:`; these directories are to be searched for files specified in `#include` directives; if it is not defined, then no additional directories are searched beyond the current directory and any specified by `-Idir` flags.

For example, if `CPATH` is "`/home/user/include:/usr/local/group/include`" and if "`-Ikernel`" is specified on the command line, then when processing `#include "x.h"`, `x.h` will be located by searching for the following files in this following order:
```
    ./x.h
    kernel/x.h
    /home/usr/include/x.h
    /usr/local/group/include/x.h
```


## Design

The main thread (master) should place file names to be processed in the work queue. The worker threads select a file name from the work queue, scan the file to discover dependencies, add these dependencies to the result Hash Map and, if new, to the work queue.

It should be possible to adjust the number of worker threads to process the accumulated work queue in order to speed up the processing. Since the `Work Queue` and the `Hash Map` are shared between threads, use concurrency control mechanisms to implement thread safe access.


## Implementation

A working, sequential C++17 `dependencyDiscoverer.cpp` is provided with extensive comments that explain the design of the application. Use the documentation at [en.cppreference.com](https://en.cppreference.com) to check how the C++ standard containers are used in `dependencyDiscoverer.cpp`.

Build the program with the provided Makefile and then test it by running
```sh
    $ cd test
    $ ../dependencyDiscoverer *.y *.l *.c
```
This should produce an output identical to the provided output file, so that the following command should yield no output when the correct output is produced:
```sh
    $ ../dependencyDiscoverer *.y *.l *.c | diff - output
```

Start to make the code concurrent by creating new thread-safe Work Queue and Hash Map data structures that encapsulate the existing C++ standard containers. Create a `struct` that stores the container as a member alongside the synchronization utilities and provides a similar interface to the container, but with appropriate synchronization.

Once the data structures are thread safe, create a single thread to operate on them. Test the resulting program, and keep a working copy in case the next stage goes wrong.

Once the single threaded version works correctly, it should be straightforward to obtain the number of worker threads that should be created from the `CRAWLER_THREADS` environment variable, and create that many worker threads. A key technical challenge is to design a solution so that the main thread can determine that all of the worker threads have finished (without busy waiting) so it can harvest the information in the Hash Map.