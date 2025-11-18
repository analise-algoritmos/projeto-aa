#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/quadratic.h"

#define MAX_LINE 1024
#define MAX_NUM 1000

int cmp_int(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

void test_algorithm(void (*sort_func)(int[], int), const char* name, FILE* file) {
    char line[MAX_LINE];
    char tipo[10] = "";
    int massa_idx = 1;

    printf("\n=== %s ===\n", name);
    rewind(file);

    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#') {
            strcpy(tipo, line + 1);
            tipo[strcspn(tipo, "\r\n")] = 0;
            continue;
        }
        if (strcmp(tipo, "int") != 0) continue;

        int arr[MAX_NUM], arr_copy[MAX_NUM], arr_sorted[MAX_NUM];
        int n = 0;

        char* token = strtok(line, " \t\r\n");
        while (token && n < MAX_NUM) {
            arr[n++] = atoi(token);
            token = strtok(NULL, " \t\r\n");
        }

        memcpy(arr_copy, arr, n * sizeof(int));

        clock_t start = clock();
        sort_func(arr_copy, n);
        clock_t end = clock();

        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);

        int ok = 1;
        for (int i = 0; i < n; i++)
            if (arr_copy[i] != arr_sorted[i]) { ok = 0; break; }

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n",
               massa_idx++, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
    }
}

int main() {
    const char* relative_path = "../../data/massa.txt";
    FILE* file = fopen(relative_path, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo de massa.\n");
        return 1;
    }

    test_algorithm(bubbleSort, "Bubble Sort", file);
    test_algorithm(insertionSort, "Insertion Sort", file);
    test_algorithm(combSort, "Comb Sort", file);
    test_algorithm(selectionSort, "Selection Sort", file);
    test_algorithm(shellSort, "Shell Sort", file);
    test_algorithm(gnomeSort, "Gnome Sort", file);
    test_algorithm(shakerSort, "Shaker Sort", file);
    test_algorithm(oddEvenSort, "Odd-Even Sort", file);
    test_algorithm(pancakeSort, "Pancake Sort", file);
    test_algorithm(bitonicSort, "Bitonic Sort", file);
    fclose(file);
    return 0;
}
