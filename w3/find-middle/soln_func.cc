#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findmiddle(vector<vector<int>>& vecs, int& p) {
    // Get the total length
    int totalLength = 0;
    for (const auto& vec : vecs) {
        totalLength += vec.size();
    }

    // Check if the length is even
    if (totalLength % 2 == 0) {
        return 0; // S is even, ignore p
    }

    // Combine all the vec in vecs into one sorted merged vector
    vector<int> merged;
    for (const auto& vec : vecs) {
        merged.insert(merged.end(), vec.begin(), vec.end());
    }

    sort(merged.begin(), merged.end());
    p = merged[totalLength / 2];

    return 1;
}


// int main() {
//     vector <vector<int>> vecs = { {1,2}, {3}, {4,5} };
//     int p;

//     cout << findmiddle(vecs, p) << endl;


//     return 0;
// }