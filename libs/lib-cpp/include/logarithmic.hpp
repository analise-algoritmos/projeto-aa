#ifndef LOGARITHMIC_HPP
#define LOGARITHMIC_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>

int partition(std::vector<int>& arr, int low, int high);
void quickSort(std::vector<int>& arr, int low, int high);
void merge(std::vector<int>& arr, int l, int m, int r);
void mergeSort(std::vector<int>& arr, int l, int r);
void heapify(std::vector<int>& arr, int n, int i);
void heapSort(std::vector<int>& arr);
void introSort(std::vector<int>& arr);
void timSort(std::vector<int>& arr);
void fluxsort(std::vector<int>& arr);
void crumsort(std::vector<int>& arr);
void librarysort(std::vector<int>& arr);
void msd_radix_sort(std::vector<int>& arr);
void msd_radix_sort_in_place(std::vector<int>& arr);
void merge_insertion_sort(std::vector<int>& arr);
template <typename T>
std::vector<T> linear_sort(const std::vector<T>& arr, double SCALE = 0.001);

#endif
