#include <iostream>
#include <vector>

using namespace std;

vector<int> RotatingCornerSpiral(vector<vector<int>> &m) {
  // Check if the matrix is square
  if (m.empty() || m.size() != m[0].size()) {
    return {}; // Return empty vector if not square
  }

  int n = m.size();
  vector<int> result;
  int layers = (n + 1) / 2; // Number of layers in the square

  for (int layer = 0; layer < layers; ++layer) {
    // Get the corners of the current layer
    int start = layer;
    int end = n - layer - 1;

    // Start visiting the corners in a clockwise manner
    for (int i = 0; i < 4; ++i) {
      if (i == 0) { // Top row
        for (int j = start; j <= end; ++j) {
          result.push_back(m[start][j]);
        }
      } else if (i == 1) { // Right column
        for (int j = start + 1; j <= end; ++j) {
          result.push_back(m[j][end]);
        }
      } else if (i == 2) { // Bottom row
        for (int j = end; j >= start; --j) {
          result.push_back(m[end][j]);
        }
      } else if (i == 3) { // Left column
        for (int j = end - 1; j >= start + 1; --j) {
          result.push_back(m[j][start]);
        }
      }
    }

    // Rotate corners for the next layer
    if (layer < layers - 1) {
      // Update corners for the next layer (rotate clockwise)
      int topLeft = m[start][start];
      int topRight = m[start][end];
      int bottomRight = m[end][end];
      int bottomLeft = m[end][start];

      m[start][start] = bottomLeft; // top-left = bottom-left
      m[start][end] = topLeft;      // top-right = top-left
      m[end][end] = topRight;       // bottom-right = top-right
      m[end][start] = bottomRight;  // bottom-left = bottom-right
    }
  }

  return result;
}
