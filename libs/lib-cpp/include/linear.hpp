#ifndef LINEAR_HPP
#define LINEAR_HPP

#include <vector>
#include <string>

void countingSort(std::vector<int>& arr, int k);
void radixSort(std::vector<int>& arr);
void bucketSort(std::vector<float>& arr);
void spreadsort(std::vector<int>& arr, int left, int right);
void burstsort(std::vector<std::string>& arr);
void flashsort(std::vector<int>& arr);
void postmanSort(std::vector<int>& arr, int base);
void bead_sort(std::vector<int>& arr);
void pigeonholeSort(std::vector<int>& arr);
void bucketSortWholeKeys(std::vector<int>& arr, int b);

#endif 
