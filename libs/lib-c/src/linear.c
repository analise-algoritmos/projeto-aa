#include <stdio.h>

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
