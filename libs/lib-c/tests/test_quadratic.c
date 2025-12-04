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
    test_algorithm(cocktailShakerSort, "Cocktail Shaker Sort", file);
    test_algorithm(exchangeSort, "Exchange Sort", file);
    test_algorithm(cycleSort, "Cycle Sort", file);
    test_algorithm(recombinantSort, "Recombinant Sort", file);
    test_algorithm(icbics, "ICBICS", file);
    test_algorithm(spaghettiSort, "Spaghetti Sort", file);
    
    // Sorting Network (precisa de comparadores)
    printf("\n=== Sorting Network ===\n");
    rewind(file);
    char line_sn[MAX_LINE];
    char tipo_sn[10] = "";
    int massa_idx_sn = 1;

    while (fgets(line_sn, MAX_LINE, file)) {
        if (line_sn[0] == '#') {
            strcpy(tipo_sn, line_sn + 1);
            tipo_sn[strcspn(tipo_sn, "\r\n")] = 0;
            continue;
        }
        if (strcmp(tipo_sn, "int") != 0) continue;

        int arr_sn[MAX_NUM], arr_sorted_sn[MAX_NUM];
        int n_sn = 0;

        char* token_sn = strtok(line_sn, " \t\r\n");
        while (token_sn && n_sn < MAX_NUM) {
            arr_sn[n_sn++] = atoi(token_sn);
            token_sn = strtok(NULL, " \t\r\n");
        }

        memcpy(arr_sorted_sn, arr_sn, n_sn * sizeof(int));
        qsort(arr_sorted_sn, n_sn, sizeof(int), cmp_int);

        // Gera comparadores para bubble sort network
        Comparator* comps = malloc(n_sn * n_sn * sizeof(Comparator));
        size_t m = 0;
        for (int i = 0; i < n_sn; i++) {
            for (int j = 0; j < n_sn - i - 1; j++) {
                comps[m].i = j;
                comps[m].j = j + 1;
                m++;
            }
        }

        clock_t start_sn = clock();
        int* result = sorting_network(arr_sn, n_sn, comps, m);
        clock_t end_sn = clock();

        int ok_sn = 1;
        for (int i = 0; i < n_sn; i++)
            if (result[i] != arr_sorted_sn[i]) { ok_sn = 0; break; }

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n",
               massa_idx_sn++, ok_sn ? "OK" : "FALHA", n_sn, 
               (double)(end_sn - start_sn) / CLOCKS_PER_SEC);

        free(result);
        free(comps);
    }

    // Strand Sort (retorna resultado via parâmetros)
    printf("\n=== Strand Sort ===\n");
    rewind(file);
    char line[MAX_LINE];
    char tipo[10] = "";
    int massa_idx = 1;

    while (fgets(line, MAX_LINE, file)) {
        if (line[0] == '#') {
            strcpy(tipo, line + 1);
            tipo[strcspn(tipo, "\r\n")] = 0;
            continue;
        }
        if (strcmp(tipo, "int") != 0) continue;

        int arr[MAX_NUM], arr_sorted[MAX_NUM], out[MAX_NUM];
        int n = 0;

        char* token = strtok(line, " \t\r\n");
        while (token && n < MAX_NUM) {
            arr[n++] = atoi(token);
            token = strtok(NULL, " \t\r\n");
        }

        memcpy(arr_sorted, arr, n * sizeof(int));
        qsort(arr_sorted, n, sizeof(int), cmp_int);

        int outSz = 0;
        clock_t start = clock();
        strandSort(arr, n, out, &outSz);
        clock_t end = clock();

        int ok = 1;
        if (outSz != n) {
            ok = 0;
        } else {
            for (int i = 0; i < n; i++)
                if (out[i] != arr_sorted[i]) { ok = 0; break; }
        }

        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n",
               massa_idx++, ok ? "OK" : "FALHA", n, (double)(end - start) / CLOCKS_PER_SEC);
    }

    fclose(file);
    return 0;
}
