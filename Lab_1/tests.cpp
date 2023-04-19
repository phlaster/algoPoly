#include <iostream>
#include <vector>
#include <assert.h>

#include "largest_submatrix.hpp"



Matrix generateMatrix(int N, int M, int startRow, int startCol, int submatrixSize) {
    Matrix matrix(N, Vector(M, 0));
    for (int i = startRow; i < startRow + submatrixSize; i++) {
        for (int j = startCol; j < startCol + submatrixSize; j++) {
            matrix[i][j] = 1;
        }
    }
    return matrix;
}


bool areEqual(Vector a, Vector b) {
    if(a.size() != b.size()) return false;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) return false;
    }
    return true;
}


void testFindLargestSquareSubmatrix() {
    for (int i=1; i<=100; i++)
    {
        Matrix m = generateMatrix(10*i, 20*i, i, 2*i, 5*i);
        Vector res = findLargestSquareSubmatrix(m);
        Vector v = {i, 2*i, 5*i};
        assert(areEqual(res, v));
        std::cout << "Test " << i << " OK!" << std::endl;
    }
}


int main() {
    testFindLargestSquareSubmatrix();
    return 0;
}
