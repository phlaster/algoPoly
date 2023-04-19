#include <random>
#include <ctime>
#include "arraytypes.hpp"

Matrix createRandomMatrix(int rows, int cols, int probability=90)
{
    std::srand(std::time(nullptr));
    Matrix matrix(rows, Vector(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int chanceFor1 = rand() % 100;
            matrix[i][j] = chanceFor1 < probability ? 1 : 0;
        }
    }
    return matrix;
}
