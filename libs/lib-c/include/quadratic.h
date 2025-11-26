#ifndef QUADRATIC_H
#define QUADRATIC_H

void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void combSort(int arr[], int n);
void selectionSort(int arr[], int n);
void shellSort(int arr[], int n);
void gnomeSort(int arr[], int n);
void shakerSort(int arr[], int n);
void oddEvenSort(int arr[], int n);
void pancakeSort(int arr[], int n);
void cocktailShakerSort(int arr[], int n);
void merge(int *a, int na, int *b, int nb, int *out);
void strandSort(int *arr, int n, int *out, int *outSz);
void exchangeSort(int arr[], int n);
void recombinantSort(double arr[], int n);
void icbicsSort(int arr[], int n);
void spaghettiSort(int *arr, int n, int *out);
void sortingNetwork(const int *values, size_t n, const Comparator *comps, size_t m);

#endif