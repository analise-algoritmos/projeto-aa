#ifndef LINEAR_H
#define LINEAR_H

// --- COUNTING SORT ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
// k: valor máximo no array
void countingSort(int arr[], int n, int k);

// --- LSD RADIX SORT ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
void radixSort(int arr[], int n);

// --- BUCKET SORT ---
// arr: array de floats a ser ordenado
// n: tamanho do array
void bucketSort(float arr[], int n);

// --- SPREAD SORT ---
// arr: array de inteiros a ser ordenado
// left: índice inicial do intervalo
// right: índice final do intervalo (exclusivo)
void spreadsort(int arr[], int left, int right);

// --- BURST SORT ---
// arr: array de strings (char*) a ser ordenado
// n: tamanho do array
void burstsort(char* arr[], int n);

// --- FLASH SORT ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
void flashsort(int arr[], int n);

// --- POSTMAN SORT ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
// base: base numérica para ordenação (padrão: 10)
void postmanSort(int arr[], int n, int base);

// --- BEAD SORT ---
// arr: array de inteiros não-negativos a ser ordenado
// n: tamanho do array
void bead_sort(int arr[], int n);

// --- PIGEONHOLE SORT ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
void pigeonholeSort(int arr[], int n);

// --- INSERTION SORT ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
void insertionSort(int *arr, int n);

// --- BUCKET SORT WHOLE KEYS ---
// arr: array de inteiros a ser ordenado
// n: tamanho do array
// b: número de buckets (padrão: 10)
void bucketSortWholeKeys(int *arr, int n, int b);

#endif
