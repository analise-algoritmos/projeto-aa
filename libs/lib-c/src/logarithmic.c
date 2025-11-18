#include "logarithmic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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