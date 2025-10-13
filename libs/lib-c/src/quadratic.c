#include "../include/quadratic.h"

void bubbleSort(int values[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if (values[j] > values[j + 1]){
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int values[], int n) {
    if (n <= 1){
        return;
    }
    for (int i = 1; i < n; i++) {
        int x = values[i];
        int j = i - 1;
        while (j >= 0 && x < values[j]) {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = x;
    }
}

void combSort(int arr[], int n) {
    int gap = n;
    const float shrink = 1.3;
    int sorted = 0;

    while (!sorted) {
        gap = (int)(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = 1;
        }
        sorted = 1;
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                sorted = 0;
            }
        }
    }
}

void selectionSort(int values[], int n){
    for(int i = 0; i < n-1; i++){
        int minIndex = i;
        for(int j = i+1; j < n; j++){
            if(values[j] < values[minIndex]){
                minIndex = j;
            }
        }
        if(minIndex != i){
            int temp = values[i];
            values[i] = values[minIndex];
            values[minIndex] = temp;
        }
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j-gap] > temp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void gnomeSort(int arr[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i-1]) {
            i++;
        } else {
            int temp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = temp;
            i--;
        }
    }
}

void shakerSort(int arr[], int n) {
    int start = 0, end = n - 1;
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swapped = 1;
            }
        }
        end--;
        for (int i = end-1; i >= start; i--) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swapped = 1;
            }
        }
        start++;
    }
}

void oddEvenSort(int arr[], int n) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i = 1; i < n-1; i += 2) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                sorted = 0;
            }
        }
        for (int i = 0; i < n-1; i += 2) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                sorted = 0;
            }
        }
    }
}

void flip(int arr[], int i) {
    int start = 0;
    while (start < i) {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int findMaxIndex(int arr[], int n) {
    int mi = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[mi]) mi = i;
    return mi;
}

void pancakeSort(int arr[], int n) {
    for (int currSize = n; currSize > 1; currSize--) {
        int mi = findMaxIndex(arr, currSize);
        if (mi != currSize-1) {
            flip(arr, mi);
            flip(arr, currSize-1);
        }
    }
}
