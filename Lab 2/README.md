# Lab 2

### `queueFIFO.c`
Study the given source code implementing a FIFO queue using a linked list. Build a version of `qtest` against `queueFIFO.c` and test it. Test the implementation with the provided `test.dat`.

### `queueLIFO.c`
Starting from `queueFIFO.c`, now implement `queueLIFO.c`. The semantics here is that the most recently added element is the next item to be removed by `q_remove`. Test this to be sure that it works correctly.

### `queuePrioLL.c`
Starting from `queueFIFO.c`, generate a simple version of a priority queue. Since the semantics of a priority queue is that the next item to remove should be the highest priority in the list, this implies that the "head" member of the Queue listhead should oint to the highest priority entry in the list. In turn, this means the `add()` operation needs to determine the appropriate place in the linked list at which to insert the new entry. If there are several entries with the same priority as the new entry, the new entry should go after the last entry in the list with that priority.

Implement this version of the priority queue. Test this to make sure it works correctly.

### `queuePrioMultiLL.c`
A more efficient way to structure the priority queue when there are a reasonably small number of priorities is to have a inked list for each priority. This can be achieved using an array of `q_head` structures, one for each priority. `add()` now simply appends a new item to the appropriate linked list for that priority.

`remove()` becomes a little more complex, in that it must start at the highest priority, checking to see if there are any items in that linked list. If not, it goes to the next lower priority, and continues this until it finds a non-empty list, or reaches a priority below `MIN_PRIO`.

Implement this version of the priority queue. Test this to make sure it works correctly.

### `queuePrioHeap.c`
If the number of items to be stored in the queue is bounded, a heap structure can be used to maintain a priority queue.

Design and implement a priority queue using a heap. Allocate an array statically to hold the queue elements; this means that `q_add()` may fail if the array is already full. Compare it against the other priority queue implementations.