#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../include/quadratic.hpp"
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

int main() {
    vector<vector<int>> massas = carregarMassas("../../../data/massa.txt");

    runAndPrint("Bubble Sort", bubbleSort, massas);
    runAndPrint("Insertion Sort", insertionSort, massas);
    runAndPrint("Selection Sort", selectionSort, massas);
    runAndPrint("Shell Sort", shellSort, massas);
    runAndPrint("Comb Sort", combSort, massas);
    runAndPrint("Gnome Sort", gnomeSort, massas);
    runAndPrint("Shaker Sort", shakerSort, massas);
    runAndPrint("Odd-Even Sort", oddEvenSort, massas);
    runAndPrint("Pancake Sort", pancakeSort, massas);
    runAndPrint("Bitonic Sort", bitonicSort, massas);
    runAndPrint("Cocktail Shaker Sort", cocktailShakerSort, massas);
    runAndPrint("Exchange Sort", exchangeSort, massas);
    runAndPrint("Cycle Sort", cycleSort, massas);
    runAndPrint("Recombinant Sort", recombinantSort, massas);
    runAndPrint("ICBICS", icbicsSort, massas);
    runAndPrint("Spaghetti Sort", spaghettiSort, massas);
    runAndPrint("Sorting Network", sortingNetwork, massas);

    // Strand Sort (recebe input e output como parâmetros)
    cout << "=== Strand Sort ===" << endl;
    int i = 1;
    for (auto arr : massas) {
        vector<int> input = arr;
        vector<int> output;
        auto start = chrono::high_resolution_clock::now();
        strandSort(input, output);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> dur = end - start;

        cout << "Massa " << i++ << ": " << (isSorted(output) ? "OK" : "ERRO")
             << ", tamanho=" << output.size()
             << ", tempo=" << fixed << setprecision(6) << dur.count() << "s" << endl;
    }
    cout << endl;

    return 0;
}