#include "functions.hpp"

void quickSort(vector<Pair>& data, int low, int high) {
    // Проверяем, что левый индекс меньше правого
    if (low < high) {
        // Устанавливаем индекс опорного элемента равным левой границе
        int pivotIndex = low;

        // Получаем значение
        int pivotValue = data[pivotIndex].second;

        // Меняем местами опорный элемент с элементом справа
        swap(data[pivotIndex], data[high]);

        // Инициализируем переменную i на левой границе
        int i = low;

        // Итерируем от левой до правой границы
        for (int j = low; j < high; j++) {
            // Если значение текущего элемента меньше опорного значения
            if (data[j].second < pivotValue) {
                // Меняем местами текущий элемент с элементом, находящимся слева от опорного
                swap(data[i], data[j]);
                i++;
            }
        }
        // Меняем местами опорный элемент с элементом, находящимся на позиции i
        swap(data[i], data[high]);

        // Рекурсивно вызываем сортировку для левой части массива
        quickSort(data, low, i - 1);
        // Рекурсивно вызываем сортировку для правой части массива
        quickSort(data, i + 1, high);
    }
}

// Перегрузка для сокрытия деталей реализации
void quickSort(vector<Pair>& data) {
    quickSort(data, 0, data.size() - 1);
}

vector<Pair> readdata(const Str& filename) {
    vector<Pair> data;  // Вектор для хранения пар 'слово-ключевое число'

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла!\n";
        return data;
    }

    Str word;
    int keyValue;
    while (inputFile >> word >> keyValue)
        data.push_back(make_pair(word, keyValue));

    inputFile.close();
    return data;
}


void printSorted(vector<Pair>& data) {
    for (const auto& entry : data)
        cout << entry.second << " " << entry.first << endl;
}

bool hasCollisions(vector<Pair>& data) {
    for (size_t i = 0; i < data.size() - 1; i++)
        if (data[i].second == data[i + 1].second)
            return true;
    return false;
}

Str wordOccurs(const vector<Pair>& data, int value) {
    for (const auto& entry : data)
        if (entry.second == value)
            return entry.first;
    return Str();
}