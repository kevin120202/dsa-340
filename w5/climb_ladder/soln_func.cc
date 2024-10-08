#include <iostream>
#include <vector>
using namespace std;

int nclimbs(int n) {
  vector<int> dp(n + 1, 0); // Create a DP array of size n+1
  dp[0] = 1; // There's 1 way to reach 0 (by not taking any steps)

  // Loop through each number from 1 to n and calculate the ways to reach it
  for (int i = 1; i <= n; i++) {
    if (i - 1 >= 0)
      dp[i] += dp[i - 1]; // Add the ways to reach i-1
    if (i - 2 >= 0)
      dp[i] += dp[i - 2]; // Add the ways to reach i-2
    if (i - 3 >= 0)
      dp[i] += dp[i - 3]; // Add the ways to reach i-3
  }

  return dp[n]; // Return the number of ways to reach n
}