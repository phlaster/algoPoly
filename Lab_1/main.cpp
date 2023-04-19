#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

typedef vector<vector<int>> Matrix;
typedef vector<int> Vector;


Matrix createRandomMatrix(int rows, int cols)
{
    Matrix matrix(rows, Vector(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int chanceFor1 = rand() % 10;
            matrix[i][j] = chanceFor1 < 9 ? 1 : 0;
        }
    }
    return matrix;
}


void printMatrix(Matrix& matrix, int x=-1, int y=-1, int size=0)
{
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            if (j >= y && j < y + size && i >= x && i < x + size)
            {
                cout << "-" << matrix[i][j] << "-";
            }
            else cout << " " << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printResults(Vector& result)
{
    cout << "Top-left corner: (" << result[0] << ", " << result[1] << ")" << endl;
    cout << "Size: " << result[2] << endl;
}

/*
    This function finds the largest square submatrix of 1's in the input matrix
    using dynamic programming. It constructs a 2D DP table where each entry DP[i][j]
    represents the size of the largest square submatrix of 1's that ends at position
    (i, j) in the input matrix. The function iterates over each position in the input
    matrix and fills in the corresponding entry in the DP table using the following
    recurrence relation:

        if matrix[i][j] == 1:
        DP[i][j] = 1
        if i > 0 and j > 0:
            DP[i][j] += min(DP[i-1][j], DP[i][j-1], DP[i-1][j-1])

    After filling in the DP table, the function finds the maximum entry in the table
    and returns the corresponding position and size of the largest square submatrix.
    Note that there are other algorithms for solving this problem, such as using binary
    search over the size of the submatrix or using suffix arrays, but the DP approach
    is simple and efficient for most practical purposes.

    A DP table, also known as a memoization table, is a data structure used in dynamic programming. It is essentially a two-dimensional array that is used to store the results of subproblems that have already been solved, so that we can reuse those results later to solve larger problems.
In dynamic programming, we break down a larger problem into smaller subproblems, and solve each of those subproblems only once, storing the results in the DP table. This allows us to avoid redundant calculations and greatly improves the efficiency of our algorithm.
For example, let's say we are trying to find the minimum number of coins needed to make change for a given amount. We can create a DP table with rows representing different coin denominations, and columns representing different amounts of money. We can then fill in the table by solving smaller subproblems first, such as finding the minimum number of coins needed to make change for smaller amounts. Once we have solved all the subproblems, we can use the results in the DP table to find the solution for the original problem.
Overall, a DP table is a powerful tool that allows us to solve complex problems efficiently by breaking them down into smaller subproblems and reusing already calculated results.
*/
Vector findLargestSquareSubmatrix(Matrix& matrix, int value=1)
{
    int max_size = 0,
        max_i = -1,
        max_j = -1;
    int n = matrix.size();
    if (n == 0) return {max_i, max_j, max_size};
    int m = matrix[0].size();
    // Initialize DP table
    Matrix DP(n, Vector(m, 0));
    // Fill DP table
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == value) {
                DP[i][j] = 1;
                if (i > 0 && j > 0) {
                    DP[i][j] += min({DP[i-1][j], DP[i][j-1], DP[i-1][j-1]});
                }
                if (DP[i][j] > max_size) {
                    max_size = DP[i][j];
                    max_i = i - max_size + 1;
                    max_j = j - max_size + 1;
                }
            }
        }
    }
    return {max_i, max_j, max_size};
}


int main() {
    srand(time(nullptr));
    
    Matrix matrix = createRandomMatrix(30,30);
    Vector result = findLargestSquareSubmatrix(matrix);
    
    printMatrix(matrix, result[0], result[1], result[2]);
    printResults(result);
    return 0;
}
