#include "../include/quadratic.h"
#include <stdlib.h>
#include <math.h> 

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

void cocktailShakerSort(int arr[], int n) {
    int start = 0, end = n - 1;
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        // Passagem esquerda-direita
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        end--;
        // Passagem direita-esquerda
        for (int i = end; i > start; i--) {
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        start++;
    }
}

void merge(int *a, int na, int *b, int nb, int *out) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] < b[j])
            out[k++] = a[i++];
        else
            out[k++] = b[j++];
    }
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
}

void strandSort(int *arr, int n, int *out, int *outSz) {
    int *input = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        input[i] = arr[i];
    int inSz = n, resSz = 0;
    int *result = malloc(n * sizeof(int));
    while (inSz > 0) {
        int *strand = malloc(n * sizeof(int));
        int strandSz = 0;
        int last = input[0], si = 1;
        strand[strandSz++] = last;
        for (int i = 1; i < inSz; i++) {
            if (input[i] >= last) {
                strand[strandSz++] = input[i];
                last = input[i];
            } else {
                input[si++] = input[i];
            }
        }
        inSz = si - 1;
        int *merged = malloc(n * sizeof(int));
        merge(result, resSz, strand, strandSz, merged);
        resSz = resSz + strandSz;
        for (int i = 0; i < resSz; i++)
            result[i] = merged[i];
        free(merged);
        free(strand);
    }
    for (int i = 0; i < resSz; i++)
        out[i] = result[i];
    *outSz = resSz;
    free(result);
    free(input);
}

void exchangeSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void cycleSort(int arr[], int n) {
    for (int cycle_start = 0; cycle_start < n - 1; cycle_start++) {
        int item = arr[cycle_start];
        int pos = cycle_start;
        // Encontra a posicao correta do item
        for (int i = cycle_start + 1; i < n; i++) {
            if (arr[i] < item)
                pos++;
        }
        // Se ja esta no lugar certo, pula
        if (pos == cycle_start)
            continue;
        // Pula valores duplicados
        while (item == arr[pos])
            pos++;
        // Troca
        int temp = arr[pos];
        arr[pos] = item;
        item = temp;
        // Continua o ciclo ate retornar ao inicio
        while (pos != cycle_start) {
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++) {
                if (arr[i] < item)
                    pos++;
            }
            while (item == arr[pos])
                pos++;
            temp = arr[pos];
            arr[pos] = item;
            item = temp;
        }
    }
}

void recombinant_sort(double *arr, int n) {
    int S[10][10] = {0};   // count array
    int H_min[10];         // menor coluna usada em cada linha
    int H_max[10];         // maior coluna usada em cada linha

    // inicializa H_min/H_max
    for (int i = 0; i < 10; i++) {
        H_min[i] = 10;   // sentinel "nenhuma coluna"
        H_max[i] = -1;
    }

    // ---------- Hashing Cycle ----------
    for (int k = 0; k < n; k++) {
        double x = arr[k];

        // assume x em [0,10) com 1 casa decimal (ou arredondado para isso)
        int scaled = (int)llround(x * 10.0); // ex.: 4.5 -> 45

        if (scaled < 0 || scaled > 99) {
            // fora do intervalo suportado, aqui só ignoro;
            // em código real você trataria isso (erro ou normalização).
            continue;
        }

        int i = scaled / 10;  // parte inteira
        int j = scaled % 10;  // dígito após a vírgula

        S[i][j]++;

        if (j < H_min[i]) H_min[i] = j;
        if (j > H_max[i]) H_max[i] = j;
    }

    // ---------- Extraction Cycle ----------
    int idx = 0;
    for (int i = 0; i < 10; i++) {
        if (H_max[i] == -1) continue;  // linha vazia

        for (int j = H_min[i]; j <= H_max[i]; j++) {
            while (S[i][j] > 0) {
                arr[idx++] = (double)i + (double)j / 10.0;
                S[i][j]--;
            }
        }
    }
}

void icbics(int *arr, int n) {
    int *B = malloc(n * sizeof(int));
    memcpy(B, arr, n * sizeof(int));

    // Ordenacao canonica (Bubble Sort didatico)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (B[j] > B[j + 1]) {
                int temp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = temp;
            }

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < n; i++) {
            // Busca binaria de arr[i] em B
            int left = 0, right = n - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (B[mid] == arr[i]) {
                    if (i != mid) {
                        int temp = arr[i];
                        arr[i] = arr[mid];
                        arr[mid] = temp;
                        sorted = false;
                    }
                    break;
                } else if (B[mid] < arr[i]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
    }
    free(B);
}

void spaghettiSort(int *arr, int n, int *out) {
    bool *used = (bool*)calloc(n, sizeof(bool));
    for (int k = n - 1; k >= 0; k--) {
        int max_val = arr[0], idx = 0;
        for (int i = 0; i < n; i++) {
            if (!used[i] && arr[i] > max_val) {
                max_val = arr[i];
                idx = i;
            }
        }
        out[k] = max_val;
        used[idx] = true;
    }
    free(used);
}

typedef struct {
    size_t i, j;
} Comparator;

int* sorting_network(const int *values, size_t n,
                     const Comparator *comps, size_t m)
{
    int *a = malloc(n * sizeof(int));
    if (!a) {
    fprintf(stderr, "Erro: falha ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }
    for (size_t k = 0; k < n; k++)
        a[k] = values[k];

    for (size_t k = 0; k < m; k++) {
        size_t i = comps[k].i;
        size_t j = comps[k].j;

        if (i >= n || j >= n) {
            fprintf(stderr,
                "Erro: comparador fora dos limites: (%zu, %zu) para n=%zu\n",
                i, j, n);
            free(a);
            exit(EXIT_FAILURE);
        }

        if (a[i] > a[j]) {
            swap_int(&a[i], &a[j]);
        }
    }

    return a;
}