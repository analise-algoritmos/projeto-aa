#include "quadratic.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

void bubbleSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(vector<int>& arr) {
    size_t n = arr.size();
    if (n <= 1) return;
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = (int)i - 1; 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void combSort(vector<int>& arr) {
    size_t n = arr.size();
    int gap = (int)n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = max(1, (int)(gap / 1.3));
        swapped = false;
        for (int i = 0; i + gap < (int)n; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) swap(arr[i], arr[minIndex]);
    }
}

void shellSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            int temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void gnomeSort(vector<int>& arr) {
    size_t n = arr.size();
    size_t i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) {
            ++i;
        } else {
            swap(arr[i], arr[i - 1]);
            --i;
        }
    }
}

void shakerSort(vector<int>& arr) {
    if (arr.empty()) return;
    size_t n = arr.size();
    bool swapped = true;
    size_t start = 0;
    size_t end = n - 1;

    while (swapped) {
        swapped = false;
        for (size_t i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        if (end == 0) break;
        --end;
        for (size_t i = end; i > start; --i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++start;
    }
}

void oddEvenSort(vector<int>& arr) {
    size_t n = arr.size();
    bool sorted = false;

    while (!sorted) {
        sorted = true;
        // odd phase (i = 1,3,...)
        for (size_t i = 1; i + 1 < n; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
        // even phase (i = 0,2,...)
        for (size_t i = 0; i + 1 < n; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

int findMaxIndex(vector<int>& arr, int n) {
    int mi = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[mi]) mi = i;
    return mi;
}

void flip(vector<int>& arr, int i) {
    reverse(arr.begin(), arr.begin() + i + 1);
}

void pancakeSort(vector<int>& arr) {
    for (int curr_size = (int)arr.size(); curr_size > 1; --curr_size) {
        int mi = findMaxIndex(arr, curr_size);
        if (mi != curr_size - 1) {
            flip(arr, mi);
            flip(arr, curr_size - 1);
        }
    }
}

void bitonicSort(int *arr, int n) {
    int k, j, l, i, temp;
    for (k = 2; k <= n; k *= 2) {
        for (j = k/2; j > 0; j /= 2) {
            for (i = 0; i < n; i++) {
                l = i ^ j;
                if (l > i) {
                    if ( ((i&k)==0) && (arr[i] > arr[l]) || ( ( (i&k)!=0) && (arr[i] < arr[l])) )  {
                        temp = arr[i];
                        arr[i] = arr[l];
                        arr[l] = temp;
                    }
                }
            }
        }
    }
}