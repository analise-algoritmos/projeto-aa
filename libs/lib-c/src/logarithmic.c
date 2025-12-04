#include "logarithmic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>

#define RUN 32
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low-1;
    for (int j=low; j<high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i+1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p-1);
        quickSort(arr, p+1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    for (int i=0;i<n1;i++) L[i]=arr[l+i];
    for (int j=0;j<n2;j++) R[j]=arr[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2) arr[k++] = (L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int arr[], int l, int r) {
    if(l<r){
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if(l<n && arr[l]>arr[largest]) largest=l;
    if(r<n && arr[r]>arr[largest]) largest=r;
    if(largest != i){
        int tmp = arr[i]; arr[i]=arr[largest]; arr[largest]=tmp;
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[], int n) {
    for(int i=n/2-1;i>=0;i--) heapify(arr,n,i);
    for(int i=n-1;i>=0;i--){
        int tmp = arr[0]; arr[0]=arr[i]; arr[i]=tmp;
        heapify(arr,i,0);
    }
}

void insertionSort(int arr[], int l, int r){
    for(int i=l+1;i<=r;i++){
        int key = arr[i], j=i-1;
        while(j>=l && arr[j]>key){ arr[j+1]=arr[j]; j--; }
        arr[j+1]=key;
    }
}

void introsortRec(int arr[], int l, int r, int depthLimit){
    if(r-l <= 16){
        insertionSort(arr,l,r);
        return;
    }
    if(depthLimit==0){
        heapSort(arr+r-r, r-l+1); 
        return;
    }
    int p = partition(arr,l,r);
    introsortRec(arr,l,p-1,depthLimit-1);
    introsortRec(arr,p+1,r,depthLimit-1);
}

void introSort(int arr[], int n){
    int depthLimit = 2 * (int)log(n);
    introsortRec(arr,0,n-1,depthLimit);
}

void timInsertionSort(int arr[], int left, int right){
    for(int i=left+1;i<=right;i++){
        int key = arr[i], j=i-1;
        while(j>=left && arr[j]>key){ arr[j+1]=arr[j]; j--; }
        arr[j+1]=key;
    }
}

void mergeRuns(int arr[], int left, int mid, int right){
    int n1 = mid-left+1, n2=right-mid;
    int *L = (int*)malloc(n1*sizeof(int));
    int *R = (int*)malloc(n2*sizeof(int));
    for(int i=0;i<n1;i++) L[i]=arr[left+i];
    for(int i=0;i<n2;i++) R[i]=arr[mid+1+i];
    int i=0,j=0,k=left;
    while(i<n1 && j<n2) arr[k++] = (L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
    free(L); free(R);
}

void timsort(int arr[], int n){
    for(int i=0;i<n;i+=RUN){
        int right = (i+RUN-1<n)?i+RUN-1:n-1;
        timInsertionSort(arr,i,right);
    }
    for(int size=RUN;size<n;size*=2){
        for(int left=0; left<n; left+=2*size){
            int mid = left+size-1;
            int right = (left+2*size-1<n)?left+2*size-1:n-1;
            if(mid<right) mergeRuns(arr,left,mid,right);
        }
    }
}


static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void slowsort(int *A, int i, int j) {
    if (i >= j) {
        return;
    }
    int m = (i + j) / 2;
    slowsort(A, i, m);
    slowsort(A, m + 1, j);
    if (A[m] > A[j]) {
        swap(&A[m], &A[j]);
    }
    slowsort(A, i, j - 1);
}

void cubesort(int arr[], int n) {
    int aux[n], size = 0;
    for (int i = 0; i < n; i++) {
        int x = arr[i], j = 0;
        while (j < size && aux[j] < x)
            j++;
        for (int k = size; k > j; k--)
            aux[k] = aux[k-1];
        aux[j] = x;
        size++;
    }
    for (int i = 0; i < n; i++)
        arr[i] = aux[i];
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int array[], int from1, int to1, int from2, int to2, int buffer) {
    while (from1 <= to1 && from2 <= to2) {
        if (array[from1] <= array[from2])
            swap(&array[from1++], &array[buffer++]);
        else
            swap(&array[from2++], &array[buffer++]);
    }
    while (from1 <= to1)
        swap(&array[from1++], &array[buffer++]);
    while (from2 <= to2)
        swap(&array[from2++], &array[buffer++]);
}

void AdvancedInPlaceMergeSort(int array[], int start, int end, int buffer);

void mergeSortInPlace(int array[], int start, int end) {
    if (start < end) {
        int mid = (start + end + 1) / 2 - 1;
        int buffer = end - (mid - start);
        AdvancedInPlaceMergeSort(array, start, mid, buffer);

        int L2 = buffer, R2 = end, L1 = start, R1 = L2 - 1;

        while (R1 - L1 > 1) {
            mid = (L1 + R1) / 2;
            int len = R1 - mid - 1;
            AdvancedInPlaceMergeSort(array, mid + 1, R1, mid + 1);
            merge(array, L1, L1 + len - 1, L2, R2, R1 - len + 1);
            R1 = R1 - len;
            L2 = R1 + 1;
        }

        for (int i = R1; i >= L1; i--) {
            int j = i + 1;
            while (j <= end && array[j - 1] > array[j]) {
                swap(&array[j - 1], &array[j]);
                j++;
            }
        }
    }
}

void AdvancedInPlaceMergeSort(int array[], int start, int end, int buffer) {
    if (start >= end) {
        swap(&array[start], &array[buffer]);
    } else {
        int mid = (start + end) / 2;
        mergeSortInPlace(array, start, mid);
        mergeSortInPlace(array, mid + 1, end);
        merge(array, start, mid, mid + 1, end, buffer);
    }
}


// Tournament Sort
#define INF INT_MAX

int winner(int pos1, int pos2, int *tmp, int n) {
    int u = (pos1 >= n ? pos1 : tmp[pos1]);
    int v = (pos2 >= n ? pos2 : tmp[pos2]);
    return (tmp[u] <= tmp[v] ? u : v);
}

int create_tree(int *a, int n, int *tmp) {

    for (int i = 0; i < n; i++)
        tmp[n + i] = a[i];

    for (int i = 2*n - 1; i > 1; i -= 2) {
        int k = i / 2;
        int j = i - 1;
        tmp[k] = winner(i, j, tmp, n);
    }

    int value = tmp[tmp[1]];
    tmp[tmp[1]] = INF;
    return value;
}

int recreate(int *tmp, int n) {
    int i = tmp[1];

    while (i > 1) {
        int k = i / 2;
        int j;

        if (i % 2 == 0 && i < 2*n - 1)
            j = i + 1;
        else
            j = i - 1;

        tmp[k] = winner(i, j, tmp, n);
        i = k;
    }

    int value = tmp[tmp[1]];
    tmp[tmp[1]] = INF;
    return value;
}

void tournament_sort(int *a, int n) {

    int *tmp = malloc(sizeof(int) * (2*n));
    if (!tmp) {
        printf("Erro de memória\n");
        return;
    }

    int value = create_tree(a, n, tmp);

    for (int i = 0; i < n; i++) {
        a[i] = value;
        value = recreate(tmp, n);
    }

    free(tmp);
}

// Tree Sort

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void storeSorted(struct Node* root, int arr[], int* i) {
    if (root != NULL) {
        storeSorted(root->left, arr, i);
        arr[*i] = root->key;
        (*i)++;
        storeSorted(root->right, arr, i);
    }
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) 
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}
void treeSort(int arr[], int n) {
    struct Node* root = NULL;
    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++)
        root = insert(root, arr[i]);
    int i = 0;
    storeSorted(root, arr, &i);
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


// Block Sort
int compareInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
typedef struct {
    int *dados;
    int tamanho;
} Bloco;

int* blockSort(int *arr, int n, int blockSize, int *resultadoTamanho) {
    int numBlocos = (n + blockSize - 1) / blockSize;
    Bloco *blocos = (Bloco *) malloc(numBlocos * sizeof(Bloco));

    int k = 0;
    for (int i = 0; i < n; i += blockSize) {
        int fim = i + blockSize;
        if (fim > n) fim = n;
        int tamanhoBloco = fim - i;

        blocos[k].dados = (int *) malloc(tamanhoBloco * sizeof(int));
        blocos[k].tamanho = tamanhoBloco;

        for (int j = 0; j < tamanhoBloco; j++) {
            blocos[k].dados[j] = arr[i + j];
        }

        qsort(blocos[k].dados, tamanhoBloco, sizeof(int), compareInt);
        k++;
    }

    int *resultado = (int *) malloc(n * sizeof(int));
    int resultadoIndex = 0;

    while (numBlocos > 0) {
        int minIdx = 0;
        for (int i = 1; i < numBlocos; i++) {
            if (blocos[i].dados[0] < blocos[minIdx].dados[0]) {
                minIdx = i;
            }
        }

        resultado[resultadoIndex++] = blocos[minIdx].dados[0];
        for (int j = 1; j < blocos[minIdx].tamanho; j++) {
            blocos[minIdx].dados[j - 1] = blocos[minIdx].dados[j];
        }
        blocos[minIdx].tamanho--;

        if (blocos[minIdx].tamanho == 0) {
            free(blocos[minIdx].dados);
            for (int i = minIdx + 1; i < numBlocos; i++) {
                blocos[i - 1] = blocos[i];
            }
            numBlocos--;
        }
    }
    free(blocos);
    *resultadoTamanho = resultadoIndex;

    return resultado;
}


// Patience Sorting
typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

void initStack(Stack *s) {
    s->capacity = 4;
    s->size = 0;
    s->data = (int *) malloc(s->capacity * sizeof(int));
}

void push(Stack *s, int value) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->data = (int *) realloc(s->data, s->capacity * sizeof(int));
    }
    s->data[s->size++] = value;
}

void pop(Stack *s) {
    if (s->size > 0) {
        s->size--;
    }
}

int top(Stack *s) {
    return s->data[s->size - 1];
}

int* merge_piles(Stack *piles, int pileCount, int *resultSize) {
    int total = 0;
    for (int i = 0; i < pileCount; i++) total += piles[i].size;

    int *ans = (int *) malloc(total * sizeof(int));
    int idx = 0;

    while (pileCount > 0) {
        int minimum = INT_MAX, minIndex = -1;

        for (int i = 0; i < pileCount; i++) {
            if (top(&piles[i]) < minimum) {
                minimum = top(&piles[i]);
                minIndex = i;
            }
        }

        ans[idx++] = minimum;
        pop(&piles[minIndex]);

        if (piles[minIndex].size == 0) {
            for (int j = minIndex; j < pileCount - 1; j++)
                piles[j] = piles[j + 1];
            pileCount--;
        }
    }

    *resultSize = idx;
    return ans;
}

int* patienceSorting(int *arr, int n, int *outSize) {
    Stack *piles = NULL;
    int pileCount = 0;

    for (int i = 0; i < n; i++) {
        int placed = 0;

        for (int j = 0; j < pileCount; j++) {
            if (arr[i] < top(&piles[j])) {
                push(&piles[j], arr[i]);
                placed = 1;
                break;
            }
        }

        if (!placed) {
            piles = (Stack *) realloc(piles, (pileCount + 1) * sizeof(Stack));
            initStack(&piles[pileCount]);
            push(&piles[pileCount], arr[i]);
            pileCount++;
        }
    }

    int *result = merge_piles(piles, pileCount, outSize);
    free(piles);
    return result;
}

// Smooth Sort

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int leonardo(int k) {
    if (k < 2)
        return 1;
    return leonardo(k - 1) + leonardo(k - 2) + 1;
}

void heapify(int *arr, int start, int end) {
    int i = start;
    int j = 0;
    int k = 0;

    while (k < end - start + 1) {
        if (k & 0xAAAAAAAA) { // mesmo teste do C++
            j = j + i;
            i = i >> 1;
        } else {
            i = i + j;
            j = j >> 1;
        }
        k = k + 1;
    }

    while (i > 0) {
        j = j >> 1;
        k = i + j;
        while (k < end) {
            if (arr[k] > arr[k - i])
                break;
            swap(&arr[k], &arr[k - i]);
            k = k + i;
        }
        i = j;
    }
}

int* smooth_sort(int *arr, int n) {
    int p = n - 1;
    int q = p;
    int r = 0;

    while (p > 0) {
        if ((r & 0x03) == 0) {
            heapify(arr, r, q);
        }

        if (leonardo(r) == p) {
            r = r + 1;
        } else {
            r = r - 1;
            q = q - leonardo(r);
            heapify(arr, r, q);
            q = r - 1;
            r = r + 1;
        }

        swap(&arr[0], &arr[p]);
        p = p - 1;
    }

    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(&arr[j], &arr[j - 1]);
            j = j - 1;
        }
    }

    return arr; 
}

// Flux Sort
static void fluxInsertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void fluxsort(int *arr, int n) {
    if (n <= 16) {
        fluxInsertionSort(arr, n);
        return;
    }
    int pivot = arr[n / 2];
    int *left = malloc(n * sizeof(int));
    int *right = malloc(n * sizeof(int));
    int l = 0, r = 0, m = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < pivot)
            left[l++] = arr[i];
        else if (arr[i] == pivot)
            m++;
        else
            right[r++] = arr[i];
    }

    fluxsort(left, l);
    fluxsort(right, r);

    int idx = 0;
    for (int i = 0; i < l; i++)
        arr[idx++] = left[i];
    for (int i = 0; i < m; i++)
        arr[idx++] = pivot;
    for (int i = 0; i < r; i++)
        arr[idx++] = right[i];

    free(left);
    free(right);
}

// Crumb Sort
static void crumbInsertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void crumsort(int *arr, int n) {
    if (n <= 16) {
        crumbInsertionSort(arr, n);
        return;
    }
    int pivot = arr[n / 2];
    int *left = malloc(n * sizeof(int));
    int *right = malloc(n * sizeof(int));
    int l = 0, r = 0, m = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < pivot)
            left[l++] = arr[i];
        else if (arr[i] == pivot)
            m++;
        else
            right[r++] = arr[i];
    }

    crumsort(left, l);
    crumsort(right, r);

    int idx = 0;
    for (int i = 0; i < l; i++)
        arr[idx++] = left[i];
    for (int i = 0; i < m; i++)
        arr[idx++] = pivot;
    for (int i = 0; i < r; i++)
        arr[idx++] = right[i];

    free(left);
    free(right);
}

void librarysort(int* arr, int n) {
    float eps = 1.0;
    int size = (int)ceil((1 + eps) * n);
    int* B = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        B[i] = -1; // -1 representa gap
    int mid = size / 2;
    B[mid] = arr[0];

    for (int t = 1; t < n; t++) {
        int x = arr[t];
        // Coleta indices de B ocupado
        int insert = mid;
        for (int i = 0; i < size; i++) {
            if (B[i] != -1 && B[i] < x)
                insert = i + 1;
        }
        // Anda para frente ate achar gap
        int pos = insert;
        while (pos < size && B[pos] != -1)
            pos++;
        // Desloca para direita
        for (int k = pos; k > insert; k--)
            B[k] = B[k - 1];
        B[insert] = x;
        // (Omitida realocacao inteligente de gaps)
    }
    // Copia elementos ordenados de volta para arr
    int idx = 0;
    for (int i = 0; i < size; i++)
        if (B[i] != -1)
            arr[idx++] = B[i];
    free(B);
}

// MSD Radix Sort
static int getDigit(int num, int pos, int max_digits) {
    for (int i = 0; i < max_digits - pos - 1; i++)
        num /= 10;
    return num % 10;
}

static int getMaxDigits(int *arr, int n) {
    if (n == 0) return 0;
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    int digits = 0;
    if (max == 0) return 1;
    while (max > 0) {
        digits++;
        max /= 10;
    }
    return digits;
}

static void msdRadixSortRec(int *arr, int n, int pos, int max_digits) {
    if (n <= 1 || pos >= max_digits)
        return;
    int counts[10] = {0};
    for (int i = 0; i < n; i++) {
        int digit = getDigit(arr[i], pos, max_digits);
        counts[digit]++;
    }
    int **buckets = malloc(10 * sizeof(int*));
    for (int i = 0; i < 10; i++)
        buckets[i] = malloc(counts[i] * sizeof(int));
    int idx[10] = {0};
    for (int i = 0; i < n; i++) {
        int digit = getDigit(arr[i], pos, max_digits);
        buckets[digit][idx[digit]++] = arr[i];
    }
    int k = 0;
    for (int d = 0; d < 10; d++) {
        if (counts[d] > 0) {
            msdRadixSortRec(buckets[d], counts[d], pos + 1, max_digits);
            for (int i = 0; i < counts[d]; i++)
                arr[k++] = buckets[d][i];
        }
        free(buckets[d]);
    }
    free(buckets);
}

void msdRadixSort(int *arr, int n) {
    if (n <= 0) return;
    int max_digits = getMaxDigits(arr, n);
    msdRadixSortRec(arr, n, 0, max_digits);
}

// MSD Radix Sort In-Place
static int get_digit_in_place(int num, int pos, int max_digits) {
    for (int i = 0; i < max_digits - pos - 1; i++)
        num /= 10;
    return num % 10;
}

static void msdRadixSortInPlaceRec(int *arr, int ini, int fim, int pos, int max_digits) {
    if (fim - ini <= 1 || pos >= max_digits)
        return;

    int count[10] = {0}, start[10], cur[10];
    for (int i = ini; i < fim; i++)
        count[get_digit_in_place(arr[i], pos, max_digits)]++;

    start[0] = ini;
    for (int i = 1; i < 10; i++)
        start[i] = start[i - 1] + count[i - 1];

    for (int i = 0; i < 10; i++)
        cur[i] = start[i];

    int i = ini;
    while (i < fim) {
        int d = get_digit_in_place(arr[i], pos, max_digits);
        int j = cur[d];

        if (i != j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        } else {
            i++;
        }

        if (i == cur[d])
            cur[d]++;
    }

    for (int b = 0; b < 10; b++) {
        int s = start[b];
        int e = start[b] + count[b];
        if (count[b] > 1)
            msdRadixSortInPlaceRec(arr, s, e, pos + 1, max_digits);
    }
}

void msdRadixSortInPlace(int *arr, int n) {
    if (n <= 0) return;
    int max_digits = getMaxDigits(arr, n);
    msdRadixSortInPlaceRec(arr, 0, n, 0, max_digits);
}

// Merge Insertion Sort
static void binaryInsert(int *arr, int *n, int x) {
    int left = 0, right = *n, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid;
    }
    for (int i = *n; i > left; i--)
        arr[i] = arr[i - 1];
    arr[left] = x;
    (*n)++;
}

static void mergeInsertionSortRec(int *arr, int n, int *out) {
    if (n <= 1) {
        if (n == 1)
            out[0] = arr[0];
        return;
    }
    int npairs = n / 2;
    int *left = malloc((npairs + 1) * sizeof(int));
    int *right = malloc(npairs * sizeof(int));
    for (int i = 0; i < npairs; i++) {
        if (arr[2 * i] < arr[2 * i + 1]) {
            left[i] = arr[2 * i];
            right[i] = arr[2 * i + 1];
        } else {
            left[i] = arr[2 * i + 1];
            right[i] = arr[2 * i];
        }
    }
    if (n % 2)
        left[npairs] = arr[n - 1];
    mergeInsertionSortRec(left, npairs + (n % 2), out);
    int count = npairs + (n % 2);
    for (int i = 0; i < npairs; i++)
        binaryInsert(out, &count, right[i]);
    free(left);
    free(right);
}

void mergeInsertionSort(int *arr, int n) {
    if (n <= 0) return;
    int *out = malloc(n * sizeof(int));
    mergeInsertionSortRec(arr, n, out);
    // Copia o resultado de volta para arr
    for (int i = 0; i < n; i++)
        arr[i] = out[i];
    free(out);
}

// Linear Sort
static void linear_merge(int *arr, int *left, int leftCount, int *right, int rightCount) {
    int i = 0, j = 0, k = 0;
    while (i < leftCount && j < rightCount) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else                     arr[k++] = right[j++];
    }
    while (i < leftCount)  arr[k++] = left[i++];
    while (j < rightCount) arr[k++] = right[j++];
}

static void linear_merge_sort(int *arr, int n) {
    if (n <= 1) return;
    int mid = n / 2;
    int *left  = (int *) malloc(mid * sizeof(int));
    int *right = (int *) malloc((n - mid) * sizeof(int));
    for (int i = 0; i < mid; i++)
        left[i] = arr[i];
    for (int i = mid; i < n; i++)
        right[i - mid] = arr[i];
    linear_merge_sort(left, mid);
    linear_merge_sort(right, n - mid);
    linear_merge(arr, left, mid, right, n - mid);
    free(left);
    free(right);
}

static double now_sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + (double) tv.tv_usec * 1e-6;
}

void linear_sort(int *arr, int n, double SCALE) {
    double t0 = now_sec();
    linear_merge_sort(arr, n);
    double elapsed = now_sec() - t0;
    double target  = SCALE * (double) n;
    double remaining = target - elapsed;
    if (remaining > 0.0) {
        usleep((useconds_t)(remaining * 1e6));
    }
}
