#include "MemoryBlock.hpp"


#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP


class MemoryManager {
    MemoryBlock* head;
    int blockCounter = 0;

public:
    MemoryManager();
    ~MemoryManager();

    MemoryBlock* getHead();
    void createMemoryBlock(int size);
    void allocate(int size);
    void deallocate(int size);
    bool checkIntegrity();
};


#endif