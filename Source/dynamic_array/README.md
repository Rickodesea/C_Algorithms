# Dynamic Array

This is a C implementation of a dynamic array.
It is designed to be as powerful as C++ standards
vector, dequeue, etc.

One interesting feature of this is if you have
an existing heap-alloc array, you can pass it to
this module and it while handle it for you.
Then you can have the array returned to you at any time.

* It uses contiguous storage locations for their elements, which means that their elements can also be accessed using offsets on regular pointers to its elements.
* It's size can change dynamically
* It may allocate some extra storage to accommodate for possible growth, and thus the container may have an actual capacity greater than the storage strictly needed to contain its elements (i.e., its size). 