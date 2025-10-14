#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../include/logarithmic.hpp"
using namespace std;

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

void runAndPrint(const string& name, void (*sortFunc)(vector<int>&), vector<vector<int>> massas) {
    cout << "=== " << name << " ===" << endl;
    int i = 1;
    for (auto arr : massas) {
        auto start = chrono::high_resolution_clock::now();
        sortFunc(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> dur = end - start;

        cout << "Massa " << i++ << ": " << (isSorted(arr) ? "OK" : "ERRO")
             << ", tamanho=" << arr.size()
             << ", tempo=" << fixed << setprecision(6) << dur.count() << "s" << endl;
    }
    cout << endl;
}

vector<vector<int>> carregarMassas(const string& caminho) {
    ifstream file(caminho);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << caminho << endl;
        exit(1);
    }

    vector<vector<int>> massas;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        vector<int> v;
        int num;
        while (ss >> num) v.push_back(num);
        if (!v.empty()) massas.push_back(v);
    }
    return massas;
}

// Wrappers para os algoritmos que precisam de parâmetros adicionais
void quickSortWrapper(vector<int>& arr) {
    if (!arr.empty()) quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
}

void mergeSortWrapper(vector<int>& arr) {
    if (!arr.empty()) mergeSort(arr, 0, static_cast<int>(arr.size()) - 1);
}

void heapSortWrapper(vector<int>& arr) {
    heapSort(arr);
}

void introSortWrapper(vector<int>& arr) {
    if (!arr.empty()) introSort(arr);
}

void timSortWrapper(vector<int>& arr) {
    if (!arr.empty()) timSort(arr);
}

int main() {
    vector<vector<int>> massas = carregarMassas("../../data/massa.txt");

    runAndPrint("Quick Sort", quickSortWrapper, massas);
    runAndPrint("Merge Sort", mergeSortWrapper, massas);
    runAndPrint("Heap Sort", heapSortWrapper, massas);
    runAndPrint("Intro Sort", introSortWrapper, massas);
    runAndPrint("Tim Sort", timSortWrapper, massas);

    return 0;
}
