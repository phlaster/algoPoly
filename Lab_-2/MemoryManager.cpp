#include "MemoryManager.hpp"
#include "MemoryBlock.hpp"

#include <climits>
#include <iostream>

using namespace std;

MemoryManager::MemoryManager() {
    head = nullptr;
    cout << "Запущен менеджер памяти\n";
}

MemoryManager::~MemoryManager() {
    MemoryBlock* current = head;
    while (current != nullptr) {
        MemoryBlock* next = current->next;
        delete current;
        current = next;
    }
    cout << "Менеджер памяти завершает работу\n";
}

MemoryBlock* MemoryManager::getHead(){
    return this->head;
}


void MemoryManager::createMemoryBlock(int size) {
    cout << "Выделение блока памяти размером " << size << "\n";
    MemoryBlock *newBlock = new MemoryBlock();
    newBlock->id = ++this->blockCounter;
    newBlock->size = size;
    newBlock->isOccupied = false;
    newBlock->next = head;
    head = newBlock;
}


/*
4. Реализация метода `allocate` для выделения памяти.
   Мы будем использовать стратегию "best fit", поэтому нам нужно найти блок
   с наименьшим размером, который достаточен для требуемого размера. Затем мы
   будем разделять найденный блок на две части - занятую и свободную.
*/
void MemoryManager::allocate(int size) {
    cout << "Аллокация: " << size << "\n";
    MemoryBlock* current = head;
    MemoryBlock* bestFit = nullptr;
    int minSizeDiff = INT_MAX;

    // Поиск наименьшего подходящего блока
    while (current != nullptr) {
        if (!current->isOccupied && current->size >= size) {
            int currentSizeDiff = current->size - size;
            if (currentSizeDiff < minSizeDiff) {
                minSizeDiff = currentSizeDiff;
                bestFit = current;
            }
        }
        current = current->next;
    }

    // Если блок найден, разделяем его на две части
    if (bestFit != nullptr) {
        MemoryBlock* newBlock = new MemoryBlock();
        newBlock->id = ++this->blockCounter;
        newBlock->size = size;
        newBlock->isOccupied = true;
        newBlock->next = bestFit->next;
        bestFit->size -= size;
        bestFit->next = newBlock;
    }
}

/*
5. Реализация метода `deallocate` для освобождения памяти.
   Нам нужно найти блок, который нужно освободить, и пометить его
   как свободный. Если следующий блок в списке также свободен, мы
   можем объединить их.
*/

void MemoryManager::deallocate(int size) {
    cout << "Деаллокация: " << size << "\n";


    MemoryBlock* current = head;

    // Поиск блока для освобождения
    while (current != nullptr) {
        if (current->isOccupied && current->size == size) {
            current->isOccupied = false;

            // Проверка следующего блока
            if (current->next != nullptr && !current->next->isOccupied) {
                current->size += current->next->size;
                MemoryBlock* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }

            break;
        }
        current = current->next;
    }
}

/*6. Реализация метода `checkIntegrity` для проверки целостности списка.
   Мы просто проверяем, что все блоки в списке должны быть либо занятыми, либо свободными.
*/
// bool MemoryManager::checkIntegrity() {
//     cout << "Проверка целостности памяти... ";

//     MemoryBlock* current = head;

//     while (current != nullptr) {
//         if (current->isOccupied && current->next != nullptr && current->next->isOccupied) {
//             cout << "ошибка!\n";
//             return false;
//         }
//         if (!current->isOccupied) {
//             cout << "ошибка!\n";
//             return false;
//         }
//         if (!current->isOccupied && current->next != nullptr && !current->next->isOccupied) {
//             cout << "ошибка!\n";
//             return false;
//         }
//         current = current->next;
//     }

//     cout << "успешно!\n";
//     return true;
// }

bool MemoryManager::checkIntegrity() {
    std::cout << "Проверка целостности памяти... ";

    MemoryBlock* current = head;

    while (current != nullptr) {
        if (current->isOccupied && current->next != nullptr && current->next->isOccupied) {
            std::cout << "Ошибка: блоки " << current->size << " и " << current->next->size << " заняты!\n";
            return false;
        }
        if (!current->isOccupied && current->next != nullptr && !current->next->isOccupied) {
            std::cout << "Ошибка: блоки " << current->size << " и " << current->next->size << " свободны!\n";
            return false;
        }
        current = current->next;
    }

    std::cout << "успешно!\n";
    return true;
}
