#ifndef LOGARITHMIC_HPP
#define LOGARITHMIC_HPP

#include <vector>

int partition(std::vector<int>& arr, int low, int high);
void quickSort(std::vector<int>& arr, int low, int high);
void merge(std::vector<int>& arr, int l, int m, int r);
void mergeSort(std::vector<int>& arr, int l, int r);
void heapify(std::vector<int>& arr, int n, int i);
void heapSort(std::vector<int>& arr);
void introSort(std::vector<int>& arr);
void timSort(std::vector<int>& arr);

#endif
