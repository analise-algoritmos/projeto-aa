#include "logarithmic.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    size_t i = 0, j = 0;
    int k = l;
    while (i < left.size() && j < right.size()) {
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

static void insertionSort(vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static void introsortRec(vector<int>& arr, int l, int r, int depthLimit) {
    if (r - l <= 16) {
        insertionSort(arr, l, r);
        return;
    }
    if (depthLimit == 0) {
        make_heap(arr.begin() + l, arr.begin() + r + 1);
        sort_heap(arr.begin() + l, arr.begin() + r + 1);
        return;
    }
    int p = partition(arr, l, r);
    introsortRec(arr, l, p - 1, depthLimit - 1);
    introsortRec(arr, p + 1, r, depthLimit - 1);
}

void introSort(vector<int>& arr) {
    int depthLimit = static_cast<int>(2 * log(arr.size()));
    introsortRec(arr, 0, static_cast<int>(arr.size()) - 1, depthLimit);
}

#define RUN 32

void timInsertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i], j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

vector<int> mergeRuns(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    result.reserve(left.size() + right.size());
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) result.push_back(left[i++]);
        else result.push_back(right[j++]);
    }
    while (i < left.size()) result.push_back(left[i++]);
    while (j < right.size()) result.push_back(right[j++]);
    return result;
}

void timSort(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n; i += RUN)
        timInsertionSort(arr, i, min(i + RUN - 1, n - 1));

    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size;
            int right = min(left + 2 * size, n);
            if (mid < right) {
                vector<int> merged = mergeRuns(
                    vector<int>(arr.begin() + left, arr.begin() + mid),
                    vector<int>(arr.begin() + mid, arr.begin() + right)
                );
                copy(merged.begin(), merged.end(), arr.begin() + left);
            }
        }
    }
}


void slowsort(vector<int>& A, int i, int j) {
    if (i >= j) {
        return;
    }
    int m = (i + j) / 2;
    slowsort(A, i, m);
    slowsort(A, m + 1, j);
    if (A[m] > A[j]) {
        swap(A[m], A[j]);
    }
    slowsort(A, i, j - 1);
}
