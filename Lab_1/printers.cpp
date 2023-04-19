#include <iostream>
#include "arraytypes.hpp"

void printMatrix(Matrix& matrix, int x=-1, int y=-1, int size=0)
{
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            if (j >= y && j < y + size && i >= x && i < x + size)
            {
                std::cout << "-" << matrix[i][j] << "-";
            }
            else std::cout << " " << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void printResults(Vector& result)
{
    std::cout << "Top-left corner: (" << result[0] << ", " << result[1] << ")" << std::endl;
    std::cout << "Size: " << result[2] << std::endl;
}
