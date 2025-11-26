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
void spreadsort(vector<int>& arr, int left, int right);
void burstsort(vector<string>& arr);
void flashsort(vector<int>& arr);
void postmanSort(vector<int>& arr, int base);
void bead_sort(vector<int>& arr);
void pigeonholeSort(vector<int>& arr);
void bucketSortWholeKeys(vector<int>& arr, int b);

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

    vector<string> algoritmos = {"Counting Sort", "Radix Sort", "Bucket Sort", "Spread Sort", "Burst Sort", "Flash Sort", "Postman Sort", "Bead Sort", "Pigeonhole Sort", "Bucket Sort Whole Keys"};

    for (const string& alg : algoritmos) {
        cout << "\n=== " << alg << " ===\n";

        int idx = 1;
        for (auto& [tipoLinha, valores] : linhas) {
            if ((alg == "Counting Sort" || alg == "Radix Sort" || alg == "Spread Sort" || alg == "Flash Sort" || alg == "Postman Sort" || alg == "Bead Sort" || alg == "Pigeonhole Sort" || alg == "Bucket Sort Whole Keys") && tipoLinha != "int") {
                idx++;
                continue;
            }
            if (alg == "Bucket Sort" && tipoLinha != "float") {
                idx++;
                continue;
            }
            if (alg == "Burst Sort" && tipoLinha != "int" && tipoLinha != "float") {
                idx++;
                continue;
            }

            if (alg == "Burst Sort") {
                // Burst Sort (converte int ou float para strings)
                vector<string> arr_str;
                if (tipoLinha == "int") {
                    vector<int> arr_int;
                    for (auto& v : valores) arr_int.push_back(stoi(v));
                    for (auto& num : arr_int) arr_str.push_back(to_string(num));
                } else if (tipoLinha == "float") {
                    vector<float> arr_float;
                    for (auto& v : valores) arr_float.push_back(stof(v));
                    for (auto& num : arr_float) arr_str.push_back(to_string(num));
                }

                auto esperado = arr_str;
                sort(esperado.begin(), esperado.end());

                auto start = chrono::high_resolution_clock::now();
                burstsort(arr_str);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> dur = end - start;

                bool correto = verificarCorretude(arr_str, esperado);
                cout << "Massa " << idx << ": " << (correto ? "OK" : "FALHA")
                     << ", tamanho=" << arr_str.size()
                     << ", tempo=" << dur.count() << "s\n";
            } else if (tipoLinha == "int") {
                vector<int> arr;
                for (auto& v : valores) arr.push_back(stoi(v));

                // Bead Sort funciona apenas com inteiros não-negativos
                if (alg == "Bead Sort") {
                    bool all_non_negative = true;
                    for (int num : arr) {
                        if (num < 0) {
                            all_non_negative = false;
                            break;
                        }
                    }
                    if (!all_non_negative) {
                        idx++;
                        continue; // Pula arrays com valores negativos
                    }
                }

                auto esperado = arr;
                sort(esperado.begin(), esperado.end());

                auto start = chrono::high_resolution_clock::now();
                if (alg == "Counting Sort") countingSort(arr, arr.empty() ? 0 : *max_element(arr.begin(), arr.end()));
                if (alg == "Radix Sort") radixSort(arr);
                if (alg == "Spread Sort") spreadsort(arr, 0, arr.size());
                if (alg == "Flash Sort") flashsort(arr);
                if (alg == "Postman Sort") postmanSort(arr, 10);
                if (alg == "Bead Sort") bead_sort(arr);
                if (alg == "Pigeonhole Sort") pigeonholeSort(arr);
                if (alg == "Bucket Sort Whole Keys") bucketSortWholeKeys(arr, 10);
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
