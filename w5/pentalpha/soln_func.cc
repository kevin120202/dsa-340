#include <iostream>
#include <vector>

using namespace std;

// Adjacency list to represent the valid moves on the pentagram
vector<vector<int>> valid_moves = {
    {3, 7}, // From intersection 0, you can go to 3 or 7
    {4, 6}, // From intersection 1, you can go to 4 or 6
    {5, 9}, // From intersection 2, you can go to 5 or 9
    {0, 8}, // From intersection 3, you can go to 0 or 8
    {1, 9}, // From intersection 4, you can go to 1 or 9
    {2, 7}, // From intersection 5, you can go to 2 or 7
    {1, 8}, // From intersection 6, you can go to 1 or 8
    {0, 5}, // From intersection 7, you can go to 0 or 5
    {3, 6}, // From intersection 8, you can go to 3 or 6
    {2, 4}  // From intersection 9, you can go to 2 or 4
};

bool solve_pentalpha(vector<int> &place_order, vector<bool> &used,
                     int stone_count) {
  // Base case: All 9 stones have been placed
  if (stone_count == 9) {
    return true;
  }

  // Get the current position where the last stone was placed
  int current_position = place_order[stone_count - 1];

  // Try all valid moves from the current position
  for (int next_position : valid_moves[current_position]) {
    // Check if the next position is empty
    if (!used[next_position]) {
      // Place the stone in the next position
      place_order[stone_count] = next_position;
      used[next_position] = true;

      // Recur to place the next stone
      if (solve_pentalpha(place_order, used, stone_count + 1)) {
        return true;
      }

      // Backtrack: Remove the stone and mark the position as empty again
      used[next_position] = false;
    }
  }

  // If no valid moves were found, return false
  return false;
}

bool pentalpha(int place_order[]) {
  vector<int> place_order_vec(9,
                              -1); // Initialize vector to store stone placement
  place_order_vec[0] = place_order[0]; // First stone is already placed

  vector<bool> used(10, false); // Tracks which intersections have stones
  used[place_order[0]] = true;  // The first stone is already placed

  // Try to solve the puzzle by placing the remaining 8 stones
  if (solve_pentalpha(place_order_vec, used, 1)) {
    // Copy the result back to the original array
    for (int i = 0; i < 9; ++i) {
      place_order[i] = place_order_vec[i];
    }
    return true;
  }
  return false;
}
