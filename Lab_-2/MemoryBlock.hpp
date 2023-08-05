#ifndef MEMORY_BLOCK_HPP
#define MEMORY_BLOCK_HPP

struct MemoryBlock {
    int id;
    int size;
    bool isOccupied;
    MemoryBlock* next;
};


#endif