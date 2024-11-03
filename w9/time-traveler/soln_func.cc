#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mintimesteps(int a[], int len, int n) {
    int steps = 0, currentEnd = 0, furthest = 0;

    for (int i = 0; i < len; ++i) {
        if (i > furthest) {
            return -1;
        }

        furthest = max(furthest, i + a[i]);

        if (i == currentEnd) {
            steps++;
            currentEnd = furthest;

            if (currentEnd >= n) {
                return steps;
            }
        }
    }

    return -1;
}

