#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/logarithmic.h"

#define MAX_LINE 100000

int isSorted(int arr[], int n){
    for(int i=1;i<n;i++) if(arr[i]<arr[i-1]) return 0;
    return 1;
}

void runAndPrint(const char* name, void (*sortFunc)(int*, int), int **massas, int *sizes, int count){
    printf("=== %s ===\n", name);
    for(int i=0;i<count;i++){
        int *arr = (int*)malloc(sizes[i]*sizeof(int));
        memcpy(arr,massas[i],sizes[i]*sizeof(int));
        clock_t start = clock();
        sortFunc(arr,sizes[i]);
        clock_t end = clock();
        double t = (double)(end-start)/CLOCKS_PER_SEC;
        printf("Massa %d: %s, tamanho=%d, tempo=%.6fs\n", i+1,
            isSorted(arr,sizes[i])?"OK":"ERRO", sizes[i], t);
        free(arr);
    }
    printf("\n");
}

// Wrappers
void quickSortWrapper(int arr[], int n){ if(n>0) quickSort(arr,0,n-1);}
void mergeSortWrapper(int arr[], int n){ if(n>0) mergeSort(arr,0,n-1);}
void heapSortWrapper(int arr[], int n){ heapSort(arr,n);}
void introSortWrapper(int arr[], int n){ if(n>0) introSort(arr,n);}
void timsortWrapper(int arr[], int n){ if(n>0) timsort(arr,n);}
void slowSortWrapper(int arr[], int n){ if(n>0) slowsort(arr,0,n-1);}
void cubeSortWrapper(int arr[], int n){ if(n>0) cubesort(arr,n);}

int main(){
    FILE *file = fopen("../../data/massa.txt","r");
    if(!file){ printf("Erro ao abrir arquivo\n"); return 1; }

    int **massas = NULL, *sizes=NULL, count=0;
    char line[MAX_LINE];
    while(fgets(line,MAX_LINE,file)){
        if(line[0]=='#'||line[0]=='\n') continue;
        int *v=NULL, size=0;
        char *token = strtok(line," \t\n");
        while(token){
            v = (int*)realloc(v,(size+1)*sizeof(int));
            v[size++] = atoi(token);
            token=strtok(NULL," \t\n");
        }
        if(size>0){
            massas = (int**)realloc(massas,(count+1)*sizeof(int*));
            sizes = (int*)realloc(sizes,(count+1)*sizeof(int));
            massas[count]=v;
            sizes[count]=size;
            count++;
        } else free(v);
    }
    fclose(file);

    runAndPrint("Quick Sort", quickSortWrapper, massas,sizes,count);
    runAndPrint("Merge Sort", mergeSortWrapper, massas,sizes,count);
    runAndPrint("Heap Sort", heapSortWrapper, massas,sizes,count);
    runAndPrint("Intro Sort", introSortWrapper, massas,sizes,count);
    runAndPrint("Tim Sort", timsortWrapper, massas,sizes,count);
    runAndPrint("Slow Sort", slowSortWrapper, massas,sizes,count);
    runAndPrint("Cube Sort", cubeSortWrapper, massas,sizes,count);

    for(int i=0;i<count;i++) free(massas[i]);
    free(massas); free(sizes);
    return 0;
}