#include "funcs.hpp"


void Clear()
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        cout << u8"\033[2J\033[1;1H";
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

short allocateMemory(vector<MemoryBlock>& memoryBlocks, int blockSize) {
    for (short i = 0; i < (short)memoryBlocks.size(); ++i) {
        if (!memoryBlocks[i].isOccupied && memoryBlocks[i].index >= blockSize) {
            memoryBlocks[i].isOccupied = true;
            return memoryBlocks[i].index;
        }
    }
    return -1;
}

void freeMemory(vector<MemoryBlock>& memoryBlocks, short index) {
    if (index >= 0 && index < (short)memoryBlocks.size() && memoryBlocks[index].isOccupied) {
        memoryBlocks[index].isOccupied = false;
        cout << "Блок памяти "
            << index
            << " освобождён.\n";
    } else {
        cout << "\n\tНеверный индекс блока памяти или блок уже освобожден!\n\n";
    }
}

void printMemory(vector<MemoryBlock>& memoryBlocks) {
    cout << "Используемые блоки памяти:\n";
    for (short i = 0; i < (short)memoryBlocks.size(); ++i) {
        cout << "\tИндекс: "
            << memoryBlocks[i].index
            << ", Занят: "
            << (memoryBlocks[i].isOccupied ? "Да" : "Нет")
            << "\n";
    }
}