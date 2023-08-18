/*
5. Сложение разряженных матриц
Исходные матрицы зачитывать из файла. Результат выводить на экран в виде
обычной матрицы с нулями. Разряженные матрицы хранить в памяти в виде
массива списков.
*/

#include "SparseMatrix.hpp"

int main()
{
    Str name1 = "m1.txt";
    Str name2 = "m2.txt";
    Str name3 = "m_out.txt";

    cout << "Читаем из " << name1 << ":\n";
    SparseMatrix m1(name1);
    m1.print();

    cout << "Читаем из " << name2 << ":\n";
    SparseMatrix m2(name2);
    m2.print();
    
    cout << "Вычисляем m1 - m2:\n";
    SparseMatrix result = m1 - m2;
    result.print();

    cout << "Сохраняем результат в " << name3 << "...\n";
    result.saveto(name3);

    result(1,2) -= 1;
    result(3,3) = 10;
    cout << "Печать матрицы после дополнительных операций:\n";
    result.print();

    return 0;
}

