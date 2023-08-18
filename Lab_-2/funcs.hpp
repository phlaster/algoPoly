#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <vector>
#include <iostream>
using namespace std;

// Структура, реализующая блок памяти
struct MemoryBlock {
    short index;     // Двухбайтовый индекс блока
    bool isOccupied; // Флаг занятости
};

// Платформозависимая процедура очистки консоли после каждой команды
void Clear();
// Функция выделения памяти
short allocateMemory(vector<MemoryBlock>& memoryBlocks, int blockSize);
// Функция освобождения памяти
void freeMemory(vector<MemoryBlock>& memoryBlocks, short index);
// Функция печати состояния памяти
void printMemory(vector<MemoryBlock>& memoryBlocks);

#endif