#include "quadratic.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

void bubbleSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(vector<int>& arr) {
    size_t n = arr.size();
    if (n <= 1) return;
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = (int)i - 1; 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void combSort(vector<int>& arr) {
    size_t n = arr.size();
    int gap = (int)n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = max(1, (int)(gap / 1.3));
        swapped = false;
        for (int i = 0; i + gap < (int)n; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) swap(arr[i], arr[minIndex]);
    }
}

void shellSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            int temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void gnomeSort(vector<int>& arr) {
    size_t n = arr.size();
    size_t i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) {
            ++i;
        } else {
            swap(arr[i], arr[i - 1]);
            --i;
        }
    }
}

void shakerSort(vector<int>& arr) {
    if (arr.empty()) return;
    size_t n = arr.size();
    bool swapped = true;
    size_t start = 0;
    size_t end = n - 1;

    while (swapped) {
        swapped = false;
        for (size_t i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        if (end == 0) break;
        --end;
        for (size_t i = end; i > start; --i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++start;
    }
}

void oddEvenSort(vector<int>& arr) {
    size_t n = arr.size();
    bool sorted = false;

    while (!sorted) {
        sorted = true;
        // odd phase (i = 1,3,...)
        for (size_t i = 1; i + 1 < n; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
        // even phase (i = 0,2,...)
        for (size_t i = 0; i + 1 < n; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

int findMaxIndex(vector<int>& arr, int n) {
    int mi = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[mi]) mi = i;
    return mi;
}

void flip(vector<int>& arr, int i) {
    reverse(arr.begin(), arr.begin() + i + 1);
}

void pancakeSort(vector<int>& arr) {
    for (int curr_size = (int)arr.size(); curr_size > 1; --curr_size) {
        int mi = findMaxIndex(arr, curr_size);
        if (mi != curr_size - 1) {
            flip(arr, mi);
            flip(arr, curr_size - 1);
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

void cocktailShakerSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        // Passagem esquerda para direita
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // Se nao houve trocas, o array esta ordenado
        if (!swapped)
            break;

        swapped = false;
        --end;

        // Passagem direita para esquerda
        for (int i = end; i > start; --i) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Funcao para mesclar dois vetores ordenados
void merge(vector<int>& mainList, vector<int>& strand) {
    vector<int> merged;
    int i = 0, j = 0;
    while (i < mainList.size() && j < strand.size()) {
        if (mainList[i] < strand[j]) {
            merged.push_back(mainList[i++]);
        } else {
            merged.push_back(strand[j++]);
        }
    }
    // Adiciona elementos restantes
    while (i < mainList.size()) merged.push_back(mainList[i++]);
    while (j < strand.size())   merged.push_back(strand[j++]);
    mainList = merged;
}

// Funcao principal do Strand Sort
void strandSort(vector<int>& input, vector<int>& output) {
    while (!input.empty()) {
        vector<int> strand;
        strand.push_back(input[0]);
        input.erase(input.begin());
        // Cria a strand ordenada
        for (auto it = input.begin(); it != input.end(); ) {
            if (*it >= strand.back()) {
                strand.push_back(*it);
                it = input.erase(it); // Remove elemento adicionado a strand
            } else {
                ++it;
            }
        }
        // Mescla a strand com a lista resultado
        merge(output, strand);
    }
}

void exchangeSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                // Troca se fora de ordem
                swap(arr[i], arr[j]);
            }
        }
    }
}

void cycleSort(int arr[], int n) {
    for (int start = 0; start < n - 1; ++start) {
        int item = arr[start];
        int pos = start;

        // Encontra a posicao correta para o elemento atual
        for (int i = start + 1; i < n; ++i)
            if (arr[i] < item)
                ++pos;

        // Se o elemento ja esta na posicao correta, continue
        if (pos == start)
            continue;

        // Ignora duplicatas
        while (item == arr[pos])
            ++pos;

        // Faz o swap do elemento para a posicao correta
        if (pos != start)
            swap(item, arr[pos]);

        // Rotaciona o resto do ciclo
        while (pos != start) {
            pos = start;
            for (int i = start + 1; i < n; ++i)
                if (arr[i] < item)
                    ++pos;
            while (item == arr[pos])
                ++pos;
            if (item != arr[pos])
                swap(item, arr[pos]);
        }
    }
}

void recombinant_sort(std::vector<double>& arr) {
    int S[10][10] = {0};
    int H_min[10];
    int H_max[10];

    for (int i = 0; i < 10; i++) {
        H_min[i] = 10;
        H_max[i] = -1;
    }

    // ---------- Hashing Cycle ----------
    for (double x : arr) {
        int scaled = static_cast<int>(std::llround(x * 10.0));

        if (scaled < 0 || scaled > 99) {
            // fora do intervalo suportado - tratar conforme necessidade
            continue;
        }

        int i = scaled / 10;
        int j = scaled % 10;

        S[i][j]++;

        if (j < H_min[i]) H_min[i] = j;
        if (j > H_max[i]) H_max[i] = j;
    }

    // ---------- Extraction Cycle ----------
    int idx = 0;
    for (int i = 0; i < 10; i++) {
        if (H_max[i] == -1) continue;

        for (int j = H_min[i]; j <= H_max[i]; j++) {
            while (S[i][j] > 0) {
                arr[idx++] = static_cast<double>(i) + static_cast<double>(j) / 10.0;
                S[i][j]--;
            }
        }
    }
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i-1] > arr[i]) return false;
    return true;
}

void icbicsSort(vector<int>& arr) {
    srand(time(0));
    while (!isSorted(arr)) {
        int i = rand() % arr.size();
        int j = rand() % arr.size();
        swap(arr[i], arr[j]);
    }
}

void spaghettiSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Encontra o valor maximo para determinar a "altura"
    int maxVal = *max_element(arr.begin(), arr.end());
    
    vector<int> sorted;
    vector<bool> used(arr.size(), false);
    
    // Simula a "queda" dos espaguetes
    // Comeca do menor valor 
    for (int height = 0; height <= maxVal; ++height) {
        for (int i = 0; i < arr.size(); ++i) {
            if (!used[i] && arr[i] == height) {
                sorted.push_back(arr[i]);
                used[i] = true;
            }
        }
    }
    
    arr = sorted;
}

template <typename T>
vector<T> sorting_network(const vector<T>& values,
                          const vector<pair<size_t, size_t>>& comparators) {
    vector<T> a = values; // copia
    const size_t n = a.size();
    for (auto [i, j] : comparators) {
        if (i >= n || j >= n) {
            throw out_of_range("Comparador fora dos limites: (" + to_string(i) +
                               ", " + to_string(j) + ") para n=" + to_string(n));
        }
        if (a[i] > a[j]) {
            swap(a[i], a[j]);
        }
    }
    return a;
}