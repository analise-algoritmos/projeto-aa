#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// COUNTING SORT
void countingSort(int arr[], int n, int k) {
    int count[k + 1];
    int output[n];

    for (int i = 0; i <= k; i++)
        count[i] = 0;
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    for (int i = 1; i <= k; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// LSD RADIX SORT (usa counting sort adaptado internamente)
void radixSort(int arr[], int n) {
    int m = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > m)
            m = arr[i];

    int exp = 1;
    while (m / exp > 0) {
        int output[n];
        int count[10] = {0};

        // Contagem baseada no dígito atual
        for (int i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        // Soma acumulada
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Construção do array ordenado
        for (int i = n - 1; i >= 0; i--) {
            int index = (arr[i] / exp) % 10;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }

        // Copia de volta
        for (int i = 0; i < n; i++)
            arr[i] = output[i];

        exp *= 10;
    }
}

// BUCKET SORT (insertion sort inline)
void bucketSort(float arr[], int n) {
    float buckets[n][n];
    int count[n];
    for (int i = 0; i < n; i++)
        count[i] = 0;

    // Distribui os elementos nos buckets
    for (int i = 0; i < n; i++) {
        int index = (int)(n * arr[i]);
        if (index == n) index = n - 1; // evita estouro se arr[i] == 1.0
        buckets[index][count[index]++] = arr[i];
    }

    // Ordena cada bucket (insertion sort interno)
    for (int b = 0; b < n; b++) {
        for (int i = 1; i < count[b]; i++) {
            float key = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && buckets[b][j] > key) {
                buckets[b][j + 1] = buckets[b][j];
                j--;
            }
            buckets[b][j + 1] = key;
        }
    }

    // Junta os buckets
    int idx = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < count[i]; j++)
            arr[idx++] = buckets[i][j];
}

// SPREAD SORT
void spreadsort(int arr[], int left, int right) {
    if (right - left <= 1) return;

    int min = arr[left], max = arr[left];
    for (int i = left + 1; i < right; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    if (min == max) return;

    int pivot = (min + max) / 2;
    int i = left, j = right - 1;
    while (i <= j) {
        while (arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    spreadsort(arr, left, i);
    spreadsort(arr, i, right);
}

// BURST SORT
#define MAX_STR 100

typedef struct Node {
    char* str;
    struct Node* next;
} Node;

void burstsort(char* arr[], int n) {
    Node* buckets[256] = {NULL};
    for (int i = 0; i < n; i++) {
        unsigned char c = (unsigned char)arr[i][0];
        Node* node = malloc(sizeof(Node));
        node->str = arr[i];
        node->next = buckets[c];
        buckets[c] = node;
    }
    int index = 0;
    for (int i = 0; i < 256; i++) {
        Node* current = buckets[i];
        while (current) {
            arr[index++] = current->str;
            Node* tmp = current;
            current = current->next;
            free(tmp);
        }
    }
}

// FLASH SORT
void flashsort(int arr[], int n) {
    int m = (int)(0.45 * n);
    int L[m];
    for (int i = 0; i < m; i++) L[i] = 0;

    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    if (min == max) return;

    double c1 = (double)(m - 1) / (max - min);
    for (int i = 0; i < n; i++) {
        int k = (int)(c1 * (arr[i] - min));
        L[k]++;
    }
    for (int i = 1; i < m; i++) L[i] += L[i - 1];

    int count = 0, j = 0, k = m - 1;
    while (count < n) {
        while (j >= L[k]) k--;
        int evicted = arr[j];
        while (j != L[k] - 1) {
            k = (int)(c1 * (evicted - min));
            int tmp = arr[L[k] - 1];
            arr[L[k] - 1] = evicted;
            evicted = tmp;
            L[k]--;
            count++;
        }
        count++;
        j++;
    }
}

// POSTMAN SORT
void postmanSort(int arr[], int n, int base) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    int exp = 1;
    int output[n];
    while (max / exp > 0) {
        int count[base];
        for (int i = 0; i < base; i++) count[i] = 0;

        for (int i = 0; i < n; i++)
            count[(arr[i] / exp) % base]++;

        for (int i = 1; i < base; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % base] - 1] = arr[i];
            count[(arr[i] / exp) % base]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];

        exp *= base;
    }
}

// BEAD SORT
void bead_sort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    int **beads = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        beads[i] = calloc(max, sizeof(int));
        for (int j = 0; j < arr[i]; j++)
            beads[i][j] = 1;
    }

    for (int j = 0; j < max; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += beads[i][j];
            beads[i][j] = 0;
        }
        for (int i = n - sum; i < n; i++)
            beads[i][j] = 1;
    }

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < max; j++)
            if (beads[i][j]) count++;
        arr[i] = count;
        free(beads[i]);
    }
    free(beads);
}

// PIGEONHOLE SORT
void pigeonholeSort(int arr[], int n) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    int size = max - min + 1;
    int *holes = calloc(size, sizeof(int));
    for (int i = 0; i < n; i++)
        holes[arr[i] - min]++;
    int index = 0;
    for (int i = 0; i < size; i++) {
        while (holes[i]-- > 0)
            arr[index++] = i + min;
    }
    free(holes);
}

// INSERTION SORT (auxiliar para bucketSortWholeKeys)
void insertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// BUCKET SORT WHOLE KEYS
void bucketSortWholeKeys(int *arr, int n, int b) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    if (min == max) return;
    int range = max - min + 1;
    int size = (range + b - 1) / b;
    int **buckets = malloc(b * sizeof(int*));
    int *counts = calloc(b, sizeof(int));
    for (int i = 0; i < b; i++)
        buckets[i] = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] - min) / size;
        if (idx >= b) idx = b - 1;
        buckets[idx][counts[idx]++] = arr[i];
    }
    int idx = 0;
    for (int i = 0; i < b; i++) {
        if (counts[i] > 0) {
            insertionSort(buckets[i], counts[i]);
            for (int j = 0; j < counts[i]; j++)
                arr[idx++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    free(buckets);
    free(counts);
}
