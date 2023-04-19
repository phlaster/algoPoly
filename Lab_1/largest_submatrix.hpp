#include "arraytypes.hpp"

#ifndef LARGEST_SUBMTR_HPP
#define LARGEST_SUBMTR_HPP
Vector findLargestSquareSubmatrix(Matrix& matrix, int value=1);
#endif

#ifndef CREATE_RND_MTR
#define CREATE_RND_MTR
Matrix createRandomMatrix(int rows, int cols, int probability=90);
#endif

#ifndef PRINTERS_HPP
#define PRINTERS_HPP
void printMatrix(Matrix& matrix, int x=-1, int y=-1, int size=0);
void printResults(Vector& result);
#endif
