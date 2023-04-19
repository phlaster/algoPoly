#include "largest_submatrix.hpp"
/*
    This solution finds the largest square submatrix of 1's in the input matrix
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

    A DP table, also known as a memoization table, is a data structure used in dynamic
    programming. It is essentially a two-dimensional array that is used to store the
    results of subproblems that have already been solved, so that we can reuse those
    results later to solve larger problems.
    
    In dynamic programming, we break down a larger problem into smaller subproblems,
    and solve each of those subproblems only once, storing the results in the DP table.
    This allows us to avoid redundant calculations and greatly improves the efficiency
    of our algorithm.
    
    For example, let's say we are trying to find the minimum number of coins needed to
    make change for a given amount. We can create a DP table with rows representing
    different coin denominations, and columns representing different amounts of money.
    
    We can then fill in the table by solving smaller subproblems first, such as finding
    the minimum number of coins needed to make change for smaller amounts. Once we have
    solved all the subproblems, we can use the results in the DP table to find the
    solution for the original problem.
    
    Overall, a DP table is a powerful tool that allows us to solve complex problems
    efficiently by breaking them down into smaller subproblems and reusing already
    calculated results.
*/


int main() {    
    Matrix matrix = createRandomMatrix(20,20);
    Vector result = findLargestSquareSubmatrix(matrix);
    
    printMatrix(matrix, result[0], result[1], result[2]);
    printResults(result);
    return 0;
}
