#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

void stoogesort(int arr[], int l, int h)
  {
      if (l >= h)
          return;
   
      if (arr[l] > arr[h])
          swap(arr[l], arr[h]);
   
      if (h - l + 1 > 2) {
          int t = (h - l + 1) / 3;
          stoogesort(arr, l, h - t);
          stoogesort(arr, l + t, h);
          stoogesort(arr, l, h - t);
      }
  }

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

bool isSorted(int a[], int n) {
    while (--n > 1)
        if (a[n] < a[n - 1])
            return false;
    return true;
}

void shuffle(int a[], int n) {
    for (int i = 0; i < n; i++)
        swap(a[i], a[rand() % n]);
}

void bogoSort(int a[], int n) {
    while (!isSorted(a, n))
        shuffle(a, n);
}