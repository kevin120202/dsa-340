// #include <algorithm>
// #include <iostream>
// #include <vector>
// using namespace std;

// void buildHanoiTower(const vector<pair<int, int>> &v, int &height, int
// &index) {
//   int n = v.size();
//   if (n == 0) {
//     height = 0;
//     index = -1;
//     return;
//   }

//   // Create a copy of the vector of disks with their original index
//   vector<pair<pair<int, int>, int>> disks;
//   for (int i = 0; i < n; ++i) {
//     disks.push_back({v[i], i});
//   }

//   // Sort disks by radius in descending order and by height in descending
//   order sort(disks.begin(), disks.end(),
//        [](const pair<pair<int, int>, int> &a,
//           const pair<pair<int, int>, int> &b) {
//          if (a.first.first != b.first.first) {
//            return a.first.first > b.first.first;
//          }
//          return a.first.second > b.first.second;
//        });

//   // dp[i] stores the maximum height of the tower ending with disk i
//   vector<int> dp(n, 0);
//   // parent[i] stores the index of the previous disk in the tower ending
//   // with
//   // disk i
//   vector<int> parent(n, -1);

//   int maxHeight = 0;
//   int topIndex = 0;

//   // Initialize dp with the height of each individual disk
//   for (int i = 0; i < n; ++i) {
//     dp[i] = disks[i].first.second;
//   }

//   // Build the highest tower
//   for (int i = 0; i < n; ++i) {
//     for (int j = 0; j < i; ++j) {
//       if (disks[j].first.first > disks[i].first.first &&
//           disks[j].first.second > disks[i].first.second) {
//         if (dp[j] + disks[i].first.second > dp[i]) {
//           dp[i] = dp[j] + disks[i].first.second;
//           parent[i] = j;
//         }
//       }
//     }
//     if (dp[i] > maxHeight) {
//       maxHeight = dp[i];
//       topIndex = i;
//     }
//   }

//   // The maximum height of the tower
//   height = maxHeight;
//   // The top disk index in the original input array
//   index = disks[topIndex].second;
// }