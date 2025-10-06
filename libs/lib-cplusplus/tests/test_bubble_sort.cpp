#include "bubble_sort.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr = {5, 3, 8, 4, 2};
    bubble_sort(arr);

    std::cout << "Resultado ordenado: ";
    for (int x : arr)
        std::cout << x << " ";
    std::cout << std::endl;
}