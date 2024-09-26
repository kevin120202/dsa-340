#include <vector>
using namespace std;

vector<int> diamondsequence(vector<vector<int>>& m) {
    // Get the size of the matrix
    int N = m.size();

    // Check if N is odd and greater than 2
    if (N % 2 == 0 || N <= 2) {
        return {};  // Return empty sequence if conditions are not met
    }

    // Calculate the middle index
    int mid = N / 2;
    vector<int> result;

    // 1. Top corner to right corner along the top row
    result.push_back(m[0][mid]);  // Top corner

    // Move Down-Right from top to right corner
    for (int i = 1; i <= mid; ++i) {
        result.push_back(m[i][mid + i]);
    }

    // 2. Right corner to bottom corner along the right column
    for (int i = 1; i <= mid; ++i) {
        result.push_back(m[mid + i][N - 1 - i]);
    }

    // 3. Bottom corner to left corner along the bottom row
    for (int i = 1; i <= mid; ++i) {
        result.push_back(m[N - 1 - i][mid - i]);
    }

    // 4. Left corner back to top corner along the left column
    for (int i = 1; i < mid; ++i) {
        result.push_back(m[mid - i][mid - i]);
    }

    return result;
}
