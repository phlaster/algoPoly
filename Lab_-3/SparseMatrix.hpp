#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>


using Mtr = std::vector<std::list<std::pair<int, double>>>;
using Str = std::string;
using namespace std;

class SparseMatrix {
private:
    Mtr matrix;
    int rows;
    int cols;

public:
    SparseMatrix(int numRows, int numCols);
    SparseMatrix(const Str& filename);

    double& operator()(int row, int col);

    SparseMatrix operator+(const SparseMatrix& other) const;

    SparseMatrix operator*(const double scalar) const;
    friend SparseMatrix operator*(const double scalar, const SparseMatrix& matrix);
    
    SparseMatrix operator-() const;
    SparseMatrix operator-(const SparseMatrix& other) const;

    void saveto(const Str& filename);
    void print();
};

#endif