#include <iostream>

int howmuchwater(unsigned int a[], int n) {
  // Check for invalid input
  if (n <= 0 || a == nullptr) {
    return -1;
  }

  int left = 0, right = n - 1;
  unsigned int max_left = 0;      // Max height from the left
  unsigned int max_right = 0;     // Max height from the right
  unsigned int water_trapped = 0; // Total trapped water

  // Traverse the array until both pointers meet
  while (left < right) {
    if (max_left <= max_right) {
      if (a[left] >= max_left) {
        max_left = a[left]; // Update max_left
      } else {
        // Water can be trapped here
        water_trapped += max_left - a[left];
      }
      left++; // Move left pointer to the right
    } else {
      if (a[right] >= max_right) {
        max_right = a[right]; // Update max_right
      } else {
        // Water can be trapped here
        water_trapped += max_right - a[right];
      }
      right--; // Move right pointer to the left
    }
  }

  return water_trapped;
}

// Function to display the wall representation and trapped water
void printWalls(unsigned int a[], int n, unsigned int water_trapped) {
  // Find the maximum height for formatting
  unsigned int max_height = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] > max_height) {
      max_height = a[i];
    }
  }

  // Print the wall representation
  for (unsigned int h = max_height; h > 0; --h) { // Changed to unsigned int
    for (int i = 0; i < n; ++i) {
      if (a[i] >= h) {
        std::cout << " b "; // Block present
      } else {
        std::cout << "   "; // No block
      }
    }
    std::cout << std::endl;
  }

  // Print the ground line
  for (int i = 0; i < n; ++i) {
    std::cout << "++"; // Ground
  }
  std::cout << std::endl;

  // Print the trapped water
  std::cout << water_trapped << std::endl; // Now water_trapped is passed
}
