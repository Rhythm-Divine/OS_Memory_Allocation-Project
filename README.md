# OS_Memory_Allocation-Project
This project is about implementing memory allocation algorithms in C++ to allocate memory to different processes using a doubly linked list. The algorithms implemented in this project are First-Fit, Best-Fit, Next-Fit and Worst-Fit.

The project contains a C++ implementation of a memory allocation class. This class contains the implementation of the above-mentioned algorithms along with a method to merge the fragmented memory blocks.

The class named "memory" is created that has four variables to keep track of the data, memory allocation, and the next and previous blocks in the memory.

The NewBlock method is used to create a new block of memory, and the printResult method is used to print the memory allocation results on the screen.

Each method takes a pointer to the head of the memory block and the size of the data to be allocated as input. These methods allocate memory based on the algorithm used, and the allocated block is marked as "allocated" in the memory. The memory is visualised using a linked list.

The mergeMemory method is used to merge the fragmented memory blocks, which are not currently being used. This method takes a reference to the head of the memory block as input.

This project is useful for anyone who wants to understand the memory allocation algorithms and implement them in their own projects. This project can be used as a reference for implementing memory allocation algorithms in any programming language.
