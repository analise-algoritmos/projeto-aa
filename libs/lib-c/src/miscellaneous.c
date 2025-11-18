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