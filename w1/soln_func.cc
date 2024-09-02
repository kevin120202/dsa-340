#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>

using namespace std;

int histogram(int a[], int len) {
    // Validation check
    if (len <= 0 || a == nullptr) {
        return 0;
    }

    map<int, int> freq;
    vector<int> order;
    unordered_set<int> seen;

    for (int i = 0; i < len; i++) {
        if (seen.find(a[i]) == seen.end()) {
            order.push_back(a[i]);
            seen.insert(a[i]);
        }
        freq[a[i]] += 1;
    }

    for (int num : order) {
        cout << num << " occurs " << freq[num] << " time(s)." << endl;
    }

    return 1;
}

// int main() {
//     // int a[] = { 7, -11, 7 };
//     // int len = 3;

//     int a[] = { 12, -4, 19, 5, 19, 6, 5, -4, -4, 7 };
//     int len = 10;

//     histogram(a, len);

//     return 0;
// }