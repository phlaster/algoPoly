#include "SparseMatrix.hpp"

// Главный конструктор - пустая разряженная матрица указанных размеров
SparseMatrix::SparseMatrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
    matrix.resize(numRows);
}

// Вспомогательный конструктор, читающий матрицу из файла
SparseMatrix::SparseMatrix(const Str& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int numRows, numCols, row, col;
        double value;
        file >> numRows >> numCols;
        this->matrix.resize(numRows);
        this->rows = numRows;
        this->cols = numCols;
        // Заполнение с использованием оператора ()
        while (file >> row >> col >> value)
            (*this)(row, col) = value;
        file.close();
    } else {
        // Здесь и далее в случае ошибки программа завершается с кодом -1
        cerr << "Не удалось прочесть файл!\n"; exit(-1);
    }
}

// Оператор, сокрывающий внутреннее представление
double& SparseMatrix::operator()(int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        auto& rowList = matrix[row]; // Получаем ссылку на список элементов в указанной строке
        auto it = find_if(rowList.begin(), rowList.end(), [col](const auto& item) {
            // Ищем элемент с указанным столбцом в текущей строке
            return item.first == col;
        });
        if (it != rowList.end())
            // Если элемент найден, возвращаем его значение
            return it->second;
        else {
            // Если элемент не найден, добавляем новую пару (столбец, значение)
            rowList.push_back(make_pair(col, 0.0));
            auto last = prev(rowList.end()); // Получаем итератор на только что добавленный элемент
            return last->second; // Возвращаем значение только что добавленного элемента
        }
    } else {
        cerr << "Элемент ("<<row<<","<<col<<") за границами матрицы!\n"; exit(-1);
    }
}

// Метод для записи представления матрицы в файл
void SparseMatrix::saveto(const Str& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << rows << " " << cols << endl;
        for (int i = 0; i < rows; i++)
            for (const auto& item : matrix[i])
            {   
                if (item.second == 0) continue; // Не записываем нулевые элементы
                file << i << " " << item.first << " " << item.second << endl;
            }
        file.close();
    } else {
        cerr << "Не удалось открыть файл для записи!\n"; exit(-1);
    }
}

// Печать матрицы в терминал
void SparseMatrix::print() {
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t";
        for (int j = 0; j < cols; j++)
            cout << (*this)(i, j) << " ";
        cout << "\n";
    }
    cout << "\n";
}

// Оператор сложения для двух матриц
SparseMatrix SparseMatrix::operator+(const SparseMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        cerr << "Matrix sizes should be the same!\n"; exit(-1);
    }
    SparseMatrix result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (const auto& item : matrix[i])
            result(i, item.first) += item.second;
    for (int i = 0; i < other.rows; i++)
        for (const auto& item : other.matrix[i])
            result(i, item.first) += item.second;
    return result;
}   

// Умножение матрицы на скаляр
SparseMatrix SparseMatrix::operator*(const double scalar) const {
    SparseMatrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (const auto& item : matrix[i])
            result(i, item.first) = scalar * item.second;
    return result;
}

// Перегрузка умножения на скаляр для коммутативности
SparseMatrix operator*(double scalar, const SparseMatrix& matrix) {
    return matrix * scalar;
}

// Оператор - для удобства записи
SparseMatrix SparseMatrix::operator-() const {
    return -1.0 * (*this);
}

// Перегрузка - для реализации полноценного вычитания
SparseMatrix SparseMatrix::operator-(const SparseMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        cerr << "Matrix sizes should be the same!\n"; exit(-1);
    }
    return -other + (*this);
}