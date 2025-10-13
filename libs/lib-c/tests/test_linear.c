#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../include/linear.h" // header com countingSort, radixSort, bucketSort

#define MAX_LINE 1024
#define MAX_NUM 1000  // tamanho máximo esperado por massa

// Comparadores para qsort
int cmp_int(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

int cmp_float(const void* a, const void* b) {
    float x = *(float*)a;
    float y = *(float*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    const char* relative_path = "../../data/massa.txt";
    FILE* file = fopen(relative_path, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo data/massa.txt\n");
        return 1;
    }

    char line[MAX_LINE];
    char tipo[10] = "";
    int massa_idx;

    // ==================== Counting Sort ====================
    printf("\n=== Counting Sort ===\n");
    rewind(file);
    massa_idx = 1;
    tipo[0] = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#') {
            sscanf(line+1, "%s", tipo);
            massa_idx = 1; // reinicia contador para novos tipos
            continue;
        }
        if (strlen(line) <= 1) continue; // ignora linhas vazias
        if (strcasecmp(tipo, "int") != 0) continue; // só int

        int arr[MAX_NUM];
        int n = 0;
        char* token = strtok(line, " \t\r\n");
        while (token && n < MAX_NUM) {
            arr[n++] = atoi(token);
            token = strtok(NULL, " \t\r\n");
        }
        if (n == 0) continue;

        int arr_copy[MAX_NUM];
        memcpy(arr_copy, arr, n * sizeof(int));

        int max_val = arr[0];
        for (int i = 1; i < n; i++) if (arr[i] > max_val) max_val = arr[i];

        clock_t start = clock();
        countingSort(arr_copy, n, max_val);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Radix Sort ====================
    printf("\n=== Radix Sort ===\n");
    rewind(file);
    massa_idx = 1;
    tipo[0] = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#') {
            sscanf(line+1, "%s", tipo);
            massa_idx = 1;
            continue;
        }
        if (strlen(line) <= 1) continue;
        if (strcasecmp(tipo, "int") != 0) continue;

        int arr[MAX_NUM];
        int n = 0;
        char* token = strtok(line, " \t\r\n");
        while (token && n < MAX_NUM) {
            arr[n++] = atoi(token);
            token = strtok(NULL, " \t\r\n");
        }
        if (n == 0) continue;

        int arr_copy[MAX_NUM];
        memcpy(arr_copy, arr, n * sizeof(int));

        clock_t start = clock();
        radixSort(arr_copy, n);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Bucket Sort ====================
    printf("\n=== Bucket Sort ===\n");
    rewind(file);
    massa_idx = 1;
    tipo[0] = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#') {
            sscanf(line+1, "%s", tipo);
            massa_idx = 1;
            continue;
        }
        if (strlen(line) <= 1) continue;
        if (strcasecmp(tipo, "float") != 0) continue;

        float arr[MAX_NUM];
        int n = 0;
        char* token = strtok(line, " \t\r\n");
        while (token && n < MAX_NUM) {
            arr[n++] = atof(token);
            token = strtok(NULL, " \t\r\n");
        }
        if (n == 0) continue;

        float arr_copy[MAX_NUM];
        memcpy(arr_copy, arr, n * sizeof(float));

        clock_t start = clock();
        bucketSort(arr_copy, n);
        clock_t end = clock();

        int ok = 1;
        float arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(float));
        qsort(arr_sorted, n, sizeof(float), cmp_float);
        for (int i = 0; i < n; i++) if (fabs(arr_copy[i] - arr_sorted[i]) > 1e-6) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    fclose(file);
    return 0;
}
