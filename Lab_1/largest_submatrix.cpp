#include <algorithm>
#include "arraytypes.hpp"

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
                    DP[i][j] += std::min({DP[i-1][j], DP[i][j-1], DP[i-1][j-1]});
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
