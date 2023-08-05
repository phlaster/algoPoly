/*
    6. Написать процедуры выделения и освобождения памяти блоками
    произвольного размера. Использовать односвязный список и стратегию 
"best fit". Написать процедуру проверки целостности списка.
*/

#include "MemoryManager.hpp"

#include <iostream>

using namespace std;

int main() {
    MemoryManager memoryManager;
    memoryManager.createMemoryBlock(100);
    memoryManager.createMemoryBlock(100);
    memoryManager.createMemoryBlock(100);
    memoryManager.allocate(90);
    memoryManager.allocate(5);
    memoryManager.allocate(10);


    bool isIntegrityOk = memoryManager.checkIntegrity();

    cout << "Результаты работы программы:\n";
    cout << "Список блоков памяти после выделения и освобождения:\n";
    MemoryBlock* current = memoryManager.getHead();
    while (current != nullptr) {
        cout << "\tId блока: " << current->id;
        cout << "\n\tРазмер блока: " << current->size;
        cout << "\n\t\tСостояние блока: " << (current->isOccupied ? "Занят" : "Свободен") << "\n";
        cout << "\t\tУказатель на следующий блок: " << current->next << "\n";
        current = current->next;
    }

    cout << "Результат проверки целостности списка: ";
    cout << (isIntegrityOk ? "ОК" : "Ошибка") << "\n";

    return 0;
}
