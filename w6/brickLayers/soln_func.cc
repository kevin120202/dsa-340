#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int canBuildInTime(int mid, const std::vector<int> &heights, int b) {
  int bricklayerCount = 1; // Start with one bricklayer
  int currentHeight = 0;   // Current height assigned to the bricklayer

  for (int height : heights) {
    if (currentHeight + height > mid) {
      // If adding this wall exceeds mid time, assign to a new bricklayer
      bricklayerCount++;
      currentHeight = height; // Start with this wall's height
      if (bricklayerCount > b) {
        return false; // Too many bricklayers needed
      }
    } else {
      currentHeight += height;
    }
  }
  return true;
}

int bricklayers(int b, int a[], int len) {
  if (b <= 0 || len <= 0)
    return -1;
  for (int i = 0; i < len; i++) {
    if (a[i] <= 0)
      return -1; // All heights must be > 0
  }

  int left = *std::max_element(a, a + len);   // Max height (base case)
  int right = std::accumulate(a, a + len, 0); // Sum of all heights (worst case)
  int result = right;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (canBuildInTime(mid, std::vector<int>(a, a + len), b)) {
      result = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return result;
}
