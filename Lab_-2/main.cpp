/*
1. Написать процедуры выделения и освобождения памяти блоками одинакового
размера. Вместо указателей использовать двухбайтовые индексы В блок добавить
дескриптор – флаг занятости. Использовать его для контроля повторного
освобождения памяти.
*/
#include "funcs.hpp"

int main() {
    vector<MemoryBlock> memoryBlocks;
    int totalBlocks;
    cout << "Введите общее количество блоков памяти: ";
    cin >> totalBlocks;

    memoryBlocks.resize(totalBlocks);
    for (short i = 0; i < totalBlocks; ++i)
    {
        memoryBlocks[i].index = i;
        memoryBlocks[i].isOccupied = false;
    }
    cout << "Выделено " << totalBlocks
        << " блоков с индексами 0.."
        << totalBlocks-1
        << ".\n";
    int choice;
    do
    {
        cout << "Опции:\n"
             << "\t1. Выделить память\n"
             << "\t2. Освободить память\n"
             << "\t3. Показать состояние памяти\n"
             << "\t4. Выйти\n"
             << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Clear();
            int blockSize;
            cout << "Введите размер блока памяти для выделения: ";
            cin >> blockSize;
            short allocatedIndex = allocateMemory(memoryBlocks, blockSize);
            if (allocatedIndex != -1)
                cout << "Выделен блок с индексом "
                    << allocatedIndex
                    << ".\n";
            else
                cout << "\n\tНе удалось выделить память!\n\n";
            break;
        }
        case 2:
            Clear();
            short freeIndex;
            cout << "Введите номер блока для освобождения: ";
            cin >> freeIndex;
            freeMemory(memoryBlocks, freeIndex);
            break;
        case 3:
            Clear();
            printMemory(memoryBlocks);
            break;
        case 4:
            Clear();
            cout << "Завершение программы.\n";
            break;
        default:
            Clear();
            cout << "\n\tНеверная команда!\n\n";
            break;
        }
    } while (choice != 4);
    return 0;
}
