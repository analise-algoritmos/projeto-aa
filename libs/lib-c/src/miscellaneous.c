#include <stdio.h>
#include <iostream>
using namespace std;

void stoogesort(int arr[], int i, int j)
  {
      int temp, k;
      if (arr[i] > arr[j])
      {
          temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
      }
      if ((i + 1) >= j)
          return;
      k = (int)((j - i + 1) / 3);
      stoogesort(arr, i, j - k);
      stoogesort(arr, i + k, j);
      stoogesort(arr, i, j - k);
  }

int isSorted(int *a, int n) {
    while (--n >= 1) {
        if (a[n] < a[n - 1]) {
            return 0;
        }
    }
    return 1;
}

void shuffle(int *a, int n) {
    int i, t, temp;
    for (i = 0;i < n;i++) {
        t = a[i];
        temp = rand() % n;
        a[i] = a[temp];
        a[temp] = t;
    }
}

void bogoSort(int *a, int n) {
    while (!isSorted(a, n)) {
        shuffle(a, n);
    }
}