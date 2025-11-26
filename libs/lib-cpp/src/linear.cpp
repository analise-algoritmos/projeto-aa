#include <vector>
#include <algorithm>
#include <list>
#include <string>
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

// SPREAD SORT
void spreadsort(vector<int>& arr, int left, int right) {
    if (right - left <= 1) return;

    int min_val = *min_element(arr.begin() + left, arr.begin() + right);
    int max_val = *max_element(arr.begin() + left, arr.begin() + right);
    if (min_val == max_val) return;

    int pivot = (min_val + max_val) / 2;
    int i = left, j = right - 1;
    while (i <= j) {
        while (arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < j) swap(arr[i++], arr[j--]);
    }
    spreadsort(arr, left, i);
    spreadsort(arr, i, right);
}

// BURST SORT
void burstsort(vector<string>& arr) {
    list<string> buckets[256];
    for (const auto& s : arr)
        buckets[(unsigned char)s[0]].push_back(s);
    arr.clear();
    for (int i = 0; i < 256; i++)
        for (auto& s : buckets[i])
            arr.push_back(s);
}

// FLASH SORT
void flashsort(vector<int>& arr) {
    int n = arr.size();
    int m = int(0.45 * n);
    vector<int> L(m, 0);
    int min_val = *min_element(arr.begin(), arr.end());
    int max_val = *max_element(arr.begin(), arr.end());
    if (min_val == max_val) return;

    double c1 = (double)(m - 1) / (max_val - min_val);
    for (int i = 0; i < n; i++) {
        int k = int(c1 * (arr[i] - min_val));
        L[k]++;
    }
    for (int i = 1; i < m; i++) L[i] += L[i - 1];

    int count = 0, j = 0, k = m - 1;
    while (count < n) {
        while (j >= L[k]) k--;
        int evicted = arr[j];
        while (j != L[k] - 1) {
            k = int(c1 * (evicted - min_val));
            swap(evicted, arr[L[k] - 1]);
            L[k]--;
            count++;
        }
        count++;
        j++;
    }
}

// POSTMAN SORT
void postmanSort(vector<int>& arr, int base) {
    int n = arr.size();
    int max_val = *max_element(arr.begin(), arr.end());
    int exp = 1;
    vector<int> output(n);
    while (max_val / exp > 0) {
        vector<int> count(base, 0);
        for (int num : arr) count[(num / exp) % base]++;
        for (int i = 1; i < base; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % base] - 1] = arr[i];
            count[(arr[i] / exp) % base]--;
        }
        arr = output;
        exp *= base;
    }
}

// BEAD SORT
void bead_sort(vector<int>& arr) {
    int n = arr.size();
    int max_val = *max_element(arr.begin(), arr.end());
    vector<vector<int>> beads(n, vector<int>(max_val, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < arr[i]; j++)
            beads[i][j] = 1;

    for (int j = 0; j < max_val; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += beads[i][j];
            beads[i][j] = 0;
        }
        for (int i = n - sum; i < n; i++)
            beads[i][j] = 1;
    }

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < max_val; j++)
            if (beads[i][j]) count++;
        arr[i] = count;
    }
}

// PIGEONHOLE SORT
void pigeonholeSort(vector<int>& arr) {
    if (arr.empty()) return;

    int min = arr[0], max = arr[0];
    for (int x : arr) {
        if (x < min) min = x;
        if (x > max) max = x;
    }

    int range = max - min + 1;
    vector<vector<int>> holes(range);

    for (int x : arr) {
        holes[x - min].push_back(x);
    }

    int k = 0;
    for (auto& hole : holes) {
        for (int x : hole) {
            arr[k++] = x;
        }
    }
}

// BUCKET SORT WHOLE KEYS
void bucketSortWholeKeys(vector<int>& arr, int b) {
    if (arr.empty()) return;

    int min = arr[0], max = arr[0];
    for (int x : arr) {
        if (x < min) min = x;
        if (x > max) max = x;
    }
    if (min == max) return;

    int range = max - min + 1;
    int size = (range + b - 1) / b; // tamanho de cada bucket
    vector<vector<int>> buckets(b);

    for (int x : arr) {
        int idx = (x - min) / size;
        if (idx >= b) idx = b - 1;
        buckets[idx].push_back(x);
    }

    int k = 0;
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end()); // ordena cada bucket
        for (int x : bucket) {
            arr[k++] = x;
        }
    }
}
