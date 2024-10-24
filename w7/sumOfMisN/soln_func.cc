#include <iostream>
#include <vector>

using namespace std;

int sumisnHelper(int a[], int len, int m, int n, int index, int currentSum,
                 int elementsUsed) {
  // Base case: if we've used exactly m elements
  if (elementsUsed == m) {
    return (currentSum == n) ? 1 : 0;
  }
  if (elementsUsed > m || index >= len) {
    return 0;
  }

  int includeCurrent = sumisnHelper(a, len, m, n, index + 1,
                                    currentSum + a[index], elementsUsed + 1);

  int excludeCurrent =
      sumisnHelper(a, len, m, n, index + 1, currentSum, elementsUsed);

  return includeCurrent || excludeCurrent;
}

int sumisn(int a[], int len, int m, int n) {
  if (len < 1 || m < 1) {
    return 0;
  }
  return sumisnHelper(a, len, m, n, 0, 0, 0);
}
