#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;

void countingSort(vector<int>& arr, int k);
void radixSort(vector<int>& arr);
void bucketSort(vector<float>& arr);

vector<string> split(const string& line) {
    stringstream ss(line);
    string item;
    vector<string> tokens;
    while (ss >> item)
        tokens.push_back(item);
    return tokens;
}

template<typename T>
bool verificarCorretude(const vector<T>& arr, const vector<T>& esperado) {
    return arr == esperado;
}

int main() {
    string massaPath = "../../data/massa.txt";
    ifstream file(massaPath);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << massaPath << endl;
        return 1;
    }

    vector<pair<string, vector<string>>> linhas;
    string tipo;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') {
            tipo = line.substr(1); // 'int' ou 'float'
            continue;
        }
        linhas.emplace_back(tipo, split(line));
    }

    vector<string> algoritmos = {"Counting Sort", "Radix Sort", "Bucket Sort"};

    for (const string& alg : algoritmos) {
        cout << "\n=== " << alg << " ===\n";

        int idx = 1;
        for (auto& [tipoLinha, valores] : linhas) {
            if ((alg == "Counting Sort" || alg == "Radix Sort") && tipoLinha != "int") {
                idx++;
                continue;
            }
            if (alg == "Bucket Sort" && tipoLinha != "float") {
                idx++;
                continue;
            }

            if (tipoLinha == "int") {
                vector<int> arr;
                for (auto& v : valores) arr.push_back(stoi(v));

                auto esperado = arr;
                sort(esperado.begin(), esperado.end());

                auto start = chrono::high_resolution_clock::now();
                if (alg == "Counting Sort") countingSort(arr, arr.empty() ? 0 : *max_element(arr.begin(), arr.end()));
                if (alg == "Radix Sort") radixSort(arr);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> dur = end - start;

                bool correto = verificarCorretude(arr, esperado);
                cout << "Massa " << idx << ": " << (correto ? "OK" : "FALHA")
                     << ", tamanho=" << arr.size()
                     << ", tempo=" << dur.count() << "s\n";
            } else if (tipoLinha == "float") {
                vector<float> arr;
                for (auto& v : valores) arr.push_back(stof(v));

                auto esperado = arr;
                sort(esperado.begin(), esperado.end());

                auto start = chrono::high_resolution_clock::now();
                bucketSort(arr);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> dur = end - start;

                bool correto = verificarCorretude(arr, esperado);
                cout << "Massa " << idx << ": " << (correto ? "OK" : "FALHA")
                     << ", tamanho=" << arr.size()
                     << ", tempo=" << dur.count() << "s\n";
            }

            idx++;
        }
    }

    return 0;
}
