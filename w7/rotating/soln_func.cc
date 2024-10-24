#include <iostream>
#include <vector>

using namespace std;

vector<int> RotatingCornerSpiral(vector<vector<int>> &m) {
  size_t n = m.size();
  for (const auto &row : m) {
    if (row.size() != n) {
      return {};
    }
  }

  vector<int> result;
  int top = 0, bottom = n - 1, left = 0, right = n - 1;

  while (top <= bottom && left <= right) {
    // Collect corners first
    result.push_back(m[top][left]);     // top-left
    result.push_back(m[top][right]);    // top-right
    result.push_back(m[bottom][right]); // bottom-right
    result.push_back(m[bottom][left]);  // bottom-left

    // Move inward
    top++;
    bottom--;
    left++;
    right--;

    // If there are still rows and columns to traverse
    if (top <= bottom && left <= right) {
      // Collect top row
      for (int currCol = left; currCol <= right; currCol++) {
        result.push_back(m[top - 1][currCol]); // last top row
      }

      // Collect right column
      for (int currRow = top; currRow <= bottom; currRow++) {
        result.push_back(m[currRow][right]); // current right column
      }

      // Collect bottom row if applicable
      if (top <= bottom) {
        for (int currCol = right - 1; currCol >= left; currCol--) {
          result.push_back(m[bottom + 1][currCol]); // last bottom row
        }
      }

      // Collect left column if applicable
      if (left <= right) {
        for (int currRow = bottom; currRow >= top; currRow--) {
          result.push_back(m[currRow][left - 1]); // current left column
        }
      }
    }
  }

  return result;
}
