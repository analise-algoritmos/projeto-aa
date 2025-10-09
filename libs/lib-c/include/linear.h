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

#endif
