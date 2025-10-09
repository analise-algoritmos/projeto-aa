#include <vector>
#include <algorithm>
using namespace std;

// COUNTING SORT
void countingSort(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> count(k + 1, 0), output(n);

    for (int num : arr)
        count[num]++;

    for (int i = 1; i <= k; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    arr = output;
}

// LSD RADIX SORT (counting sort interno)
void radixSort(vector<int>& arr) {
    int m = *max_element(arr.begin(), arr.end());

    for (int exp = 1; m / exp > 0; exp *= 10) {
        int n = arr.size();
        vector<int> output(n);
        int count[10] = {0};

        // Contagem dos dígitos
        for (int num : arr)
            count[(num / exp) % 10]++;

        // Soma acumulada
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Construção da saída
        for (int i = n - 1; i >= 0; i--) {
            int idx = (arr[i] / exp) % 10;
            output[count[idx] - 1] = arr[i];
            count[idx]--;
        }

        arr = output;
    }
}

// BUCKET SORT (insertion sort inline)
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    vector<vector<float>> buckets(n);

    // Distribuição nos buckets
    for (float num : arr) {
        int idx = int(n * num);
        if (idx == n) idx = n - 1; // evita estouro se num == 1.0
        buckets[idx].push_back(num);
    }

    // Ordenação de cada bucket (insertion sort interno)
    for (auto& b : buckets) {
        for (int i = 1; i < (int)b.size(); i++) {
            float key = b[i];
            int j = i - 1;
            while (j >= 0 && b[j] > key) {
                b[j + 1] = b[j];
                j--;
            }
            b[j + 1] = key;
        }
    }

    // Concatenação dos buckets
    arr.clear();
    for (auto& b : buckets)
        arr.insert(arr.end(), b.begin(), b.end());
}
