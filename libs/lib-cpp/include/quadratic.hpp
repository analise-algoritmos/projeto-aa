#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

#include <vector>

void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void combSort(std::vector<int>& arr);
void selectionSort(std::vector<int>& arr);
void shellSort(std::vector<int>& arr);
void gnomeSort(std::vector<int>& arr);
void shakerSort(std::vector<int>& arr);
void oddEvenSort(std::vector<int>& arr);
void pancakeSort(std::vector<int>& arr);
void cocktailShakerSort(std::vector<int>& arr);
void merge(std::vector<int>& mainList, std::vector<int>& strand);
void strandSort(std::vector<int>& input, std::vector<int>& output);
void exchangeSort(std::vector<int>& arr);
void cycleSort(int arr[], int n);
void recombinantSort(std::vector<double>& arr);
void icbicsSort(std::vector<int>& arr);
void spaghettiSort(std::vector<int>& arr);
void sortingNetwork(const std::vector<T>& values, const std::vector<std::pair<size_t, size_t>>& comparators);

#endif