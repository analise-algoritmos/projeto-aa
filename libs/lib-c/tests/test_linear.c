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

int cmp_str(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
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

    // ==================== Spread Sort ====================
    printf("\n=== Spread Sort ===\n");
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
        spreadsort(arr_copy, 0, n);
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

    // ==================== Burst Sort ====================
    printf("\n=== Burst Sort ===\n");
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
        // Burst Sort funciona com int e float (convertendo para strings)
        if (strcasecmp(tipo, "int") != 0 && strcasecmp(tipo, "float") != 0) continue;

        // Lê os valores como strings
        char* arr_str[MAX_NUM];
        char str_buf[MAX_NUM][32]; // buffer para armazenar as strings
        int n = 0;
        char* token = strtok(line, " \t\r\n");
        while (token && n < MAX_NUM) {
            snprintf(str_buf[n], sizeof(str_buf[n]), "%s", token);
            arr_str[n] = str_buf[n];
            n++;
            token = strtok(NULL, " \t\r\n");
        }
        if (n == 0) continue;

        char* arr_copy[MAX_NUM];
        char str_buf_copy[MAX_NUM][32];
        for (int i = 0; i < n; i++) {
            strcpy(str_buf_copy[i], str_buf[i]);
            arr_copy[i] = str_buf_copy[i];
        }

        // Ordena esperado usando qsort com strcmp
        char* arr_sorted[MAX_NUM];
        char str_buf_sorted[MAX_NUM][32];
        for (int i = 0; i < n; i++) {
            strcpy(str_buf_sorted[i], str_buf[i]);
            arr_sorted[i] = str_buf_sorted[i];
        }
        qsort(arr_sorted, n, sizeof(char*), cmp_str);

        clock_t start = clock();
        burstsort(arr_copy, n);
        clock_t end = clock();

        int ok = 1;
        for (int i = 0; i < n; i++) if (strcmp(arr_copy[i], arr_sorted[i]) != 0) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Flash Sort ====================
    printf("\n=== Flash Sort ===\n");
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
        flashsort(arr_copy, n);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Postman Sort ====================
    printf("\n=== Postman Sort ===\n");
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
        postmanSort(arr_copy, n, 10);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Bead Sort ====================
    printf("\n=== Bead Sort ===\n");
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

        // Verifica se todos os valores são não-negativos
        int all_non_negative = 1;
        for (int i = 0; i < n; i++)
            if (arr[i] < 0) {
                all_non_negative = 0;
                break;
            }
        if (!all_non_negative) {
            massa_idx++;
            continue; // Pula arrays com valores negativos
        }

        int arr_copy[MAX_NUM];
        memcpy(arr_copy, arr, n * sizeof(int));

        clock_t start = clock();
        bead_sort(arr_copy, n);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Pigeonhole Sort ====================
    printf("\n=== Pigeonhole Sort ===\n");
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
        pigeonholeSort(arr_copy, n);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    // ==================== Bucket Sort Whole Keys ====================
    printf("\n=== Bucket Sort Whole Keys ===\n");
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
        bucketSortWholeKeys(arr_copy, n, 10);
        clock_t end = clock();

        int ok = 1;
        int arr_sorted[MAX_NUM];
        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);
        for (int i = 0; i < n; i++) if (arr_copy[i] != arr_sorted[i]) ok = 0;

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", massa_idx, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
        massa_idx++;
    }

    fclose(file);
    return 0;
}
