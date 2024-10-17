#include <iostream>
#include <vector>
#include <climits>

int mintokens(int c, int a[], int len) {
    // Check for invalid input
    if (len < 1 || c < 1) {
        return -1;
    }

    std::vector<int> dp(c + 1, INT_MAX); // Initialize with INT_MAX
    dp[0] = 0; 

    // Fill the DP array
    for (int i = 0; i < len; i++) {
        for (int j = a[i]; j <= c; j++) {
            if (dp[j - a[i]] != INT_MAX) {
                dp[j] = std::min(dp[j], dp[j - a[i]] + 1);
            }
        }
    }

    return dp[c] == INT_MAX ? -1 : dp[c];
}

