# Lab 3

### Function Pointers
Write a C program that sorts an array of names. The names are implemented using the following struct:

```c
struct name {
    const char * first_name;
    const char * last_name;
};
typedef struct name name;
```

The names should be first sorted alphabetically by first name and then printed.
Then the names should be sorted and printed alphabetically by last name.

Use [`qsort`](https://en.cppreference.com/w/c/algorithm/qsort) for sorting, by writing a comparison function that is passed as function pointer to `qsort` and use [`strcmp`](https://en.cppreference.com/w/c/string/byte/strcmp) for comparing two strings.

### Writing RAII code
Implement a buffer with RAII that can grow beyond the size initially allocated. The buffer should be used as follows:

```c
int main() {
    buffer b(3);    // allocate space for 3 ints

    b.add(1);
    b.add(2);
    b.add(3);
    b.add(4);       // this call must allocate new memory
}
```

Buffer should follow the RAII model i.e. it should allocate memory in the constructor and free memory in the destructor. The buffer struct should be based on the following code snippet:

```c
struct buffer {
    int * ptr;
    // … maybe store some meta data

    // constructor
    buffer(int initial_size) {
        // … allocate enough memory for the given initial_size
    }

    ~buffer() {
        // … free memory
    }

    void add(int element) {
        // check if there is enough room left.
        // If not, allocate new memory with enough space and
        // copy all elements from the old memory over.
        // Ensure to not leak memory!
    }
};
typedef struct buffer buffer;
```

### Using RAII
Design a `node` structure which uses `std::unique_ptr` or `std::shared_ptr` to express unique or shared ownership of a node.

A `node` should store a single value and many pointers to neighboring nodes. Use an `std::vector`, if needed, for storing multiple pointers. A `add_edge_to( node_ptr )` member function should be implemented to create the graph structure.