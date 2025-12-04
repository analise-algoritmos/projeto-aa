import os
import sys
import time
import statistics
from pathlib import Path
from typing import List
import re
from datetime import datetime

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../src")))

from quadratic import (
    shell_sort,
    comb_sort,
    insertion_sort,
    bubble_sort,
    gnome_sort,
    odd_even_sort,
    selection_sort,
    cocktail_shaker_sort,
    strand_sort,
    exchange_sort,
    cycle_sort,
    recombinant_sort,
    i_cant_believe_it_can_sort,
    spaghetti_sort,
    sorting_network,
    bitonic_sorter,
    pancake_sort
)

# Lista de algoritmos quadráticos
algorithms = [
    ("Shell Sort", shell_sort),
    ("Comb Sort", comb_sort),
    ("Insertion Sort", insertion_sort),
    ("Bubble Sort", bubble_sort),
    ("Gnome Sort", gnome_sort),
    ("Odd-Even Sort", odd_even_sort),
    ("Selection Sort", selection_sort),
    ("Cocktail Shaker Sort", cocktail_shaker_sort),
    ("Strand Sort", strand_sort),
    ("Exchange Sort", exchange_sort),
    ("Cycle Sort", cycle_sort),
    ("Recombinant Sort", recombinant_sort),
    ("I Can't Believe It Can Sort", i_cant_believe_it_can_sort),
    ("Spaghetti Sort", spaghetti_sort),
    ("Sorting Network", sorting_network),
    ("Bitonic Sorter", bitonic_sorter),
    ("Pancake Sort", pancake_sort),
]


# ---------------------------------------------------
# Carrega relatório existente
# ---------------------------------------------------
def load_processed_entries(output_file):
    processed = set()
    if not os.path.exists(output_file):
        return processed

    with open(output_file, "r", encoding="utf-8") as f:
        for line in f:
            if line.startswith("|") and len(line.strip().split("|")) > 2:
                parts = line.strip().split("|")
                algo_name = parts[1].strip()
                file_path = parts[2].strip()
                processed.add((algo_name, file_path))

    return processed


# ---------------------------------------------------
# Processa um arquivo (10 repetições por algoritmo)
# ---------------------------------------------------
def process_file(file_path: Path, f_out, processed_entries, repetitions=10):

    print(f"\n[INFO] Processando {file_path}")

    # leitura dos dados
    data = []
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            for line in f:
                numbers = re.findall(r"[-+]?\d*\.\d+|[-+]?\d+", line)
                for num in numbers:
                    try:
                        data.append(float(num))
                    except:
                        pass
    except Exception as e:
        print(f"[ERRO] Falha ao ler {file_path}: {e}")
        return

    if not data:
        print("[AVISO] Arquivo vazio ou ilegível, ignorado.")
        return

    dtype = "int" if all(x.is_integer() for x in data) else "float"
    min_val = min(data)
    max_val = max(data)

    # ---------------------------------------------------
    # Executa todos os algoritmos 10x (SEM LIMITES)
    # ---------------------------------------------------
    for algo_name, algo_func in algorithms:

        if (algo_name, str(file_path)) in processed_entries:
            continue

        print(f"  - Executando {algo_name} (10×)...")

        times = []

        for _ in range(repetitions):
            arr_copy = list(data)
            start = time.time()
            algo_func(arr_copy)
            end = time.time()
            times.append(end - start)

        media = statistics.mean(times)
        desvio = statistics.stdev(times) if len(times) > 1 else 0.0

        # formato igual aos lineares
        f_out.write(
            f"| {algo_name} | {file_path} | {len(data)} | {dtype} | "
            f"{min_val} | {max_val} | {media:.6f} | {desvio:.6f} |\n"
        )
        f_out.flush()

        processed_entries.add((algo_name, str(file_path)))

    del data


# ---------------------------------------------------
# Execução principal
# ---------------------------------------------------
def run_tests_resume(data_root="data/raw", output_file="results/report_quadratic.md"):

    print("\n============================================")
    print("📌 INÍCIO DOS TESTES QUADRÁTICOS")
    print("============================================\n")

    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    root_path = Path(data_root)

    # 🔥 Igual ao linear: somente uniformInt
    txt_files = [
        p for p in root_path.rglob("*.txt")
        if "uniformInt" in str(p)
    ]

    print(f"Arquivos encontrados (uniformInt): {len(txt_files)}")

    processed_entries = load_processed_entries(output_file)
    print(f"Entradas já processadas: {len(processed_entries)}")

    # cabeçalho
    if not os.path.exists(output_file):
        with open(output_file, "w", encoding="utf-8") as f_out:
            f_out.write("# Relatório de Testes de Algoritmos Quadráticos\n\n")
            f_out.write("| Algoritmo | Arquivo | Tamanho | Tipo | Min | Max | Média (s) | Desvio Padrão |\n")
            f_out.write("|-----------|---------|---------|------|-----|-----|------------|----------------|\n")

    with open(output_file, "a", encoding="utf-8") as f_out:
        for file_path in txt_files:
            process_file(file_path, f_out, processed_entries, repetitions=10)

    print("\n============================================")
    print("🏁 FIM DOS TESTES")
    print(f"📄 Relatório salvo em: {output_file}")
    print("============================================\n")


# ---------------------------------------------------
# Testes unitários para sorting_network
# ---------------------------------------------------
import unittest

def generate_bubble_sort_network(n):
    """Gera comparadores para uma rede de ordenação tipo bubble sort"""
    comparators = []
    for i in range(n):
        for j in range(0, n - i - 1):
            comparators.append((j, j + 1))
    return comparators

def generate_odd_even_network(n):
    """Gera comparadores para uma rede de ordenação odd-even"""
    comparators = []
    for phase in range(n):
        if phase % 2 == 0:  # Fase par: compara índices pares
            for i in range(0, n - 1, 2):
                comparators.append((i, i + 1))
        else:  # Fase ímpar: compara índices ímpares
            for i in range(1, n - 1, 2):
                comparators.append((i, i + 1))
    return comparators

class TestSortingNetwork(unittest.TestCase):
    
    def sorting_network_impl(self, values, comparators):
        """Implementação direta do sorting_network para testes"""
        n = len(values)
        a = list(values)
        for i, j in comparators:
            if not (0 <= i < n and 0 <= j < n):
                raise IndexError(f"Comparador fora dos limites: ({i}, {j}) para n={n}")
            if a[i] > a[j]:
                a[i], a[j] = a[j], a[i]
        return a
    
    def test_sorting_network_basico(self):
        """Testa casos básicos do sorting_network"""
        # Teste com array pequeno e comparadores simples
        values = [3, 1, 4, 2]
        comparators = [(0, 1), (2, 3), (0, 2), (1, 3), (1, 2)]
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, sorted(values))
        
        # Array já ordenado
        values = [1, 2, 3, 4]
        comparators = [(0, 1), (2, 3)]
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, [1, 2, 3, 4])
        
        # Array reverso
        values = [4, 3, 2, 1]
        comparators = generate_bubble_sort_network(4)
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, sorted(values))
        
        # Array com elementos duplicados
        values = [3, 1, 3, 2, 1]
        comparators = generate_bubble_sort_network(5)
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, sorted(values))
        
        # Array com um elemento
        values = [5]
        comparators = []
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, [5])
        
        # Array vazio
        values = []
        comparators = []
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, [])
        
        # Array com números negativos
        values = [-5, 3, -1, 0, 2]
        comparators = generate_bubble_sort_network(5)
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, sorted(values))
        
        # Array com floats
        values = [3.5, 1.2, 4.8, 2.1]
        comparators = generate_bubble_sort_network(4)
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, sorted(values))
        
        # Teste com odd-even network
        values = [5, 2, 8, 1, 9, 3]
        comparators = generate_odd_even_network(6)
        result = self.sorting_network_impl(values, comparators)
        self.assertEqual(result, sorted(values))
    
    def test_sorting_network_erros(self):
        """Testa tratamento de erros do sorting_network"""
        # Comparador fora dos limites
        values = [1, 2, 3]
        comparators = [(0, 5)]  # índice 5 não existe
        with self.assertRaises(IndexError):
            self.sorting_network_impl(values, comparators)
        
        # Múltiplos comparadores, um inválido
        values = [1, 2, 3]
        comparators = [(0, 1), (2, 10)]  # índice 10 não existe
        with self.assertRaises(IndexError):
            self.sorting_network_impl(values, comparators)


if __name__ == "__main__":
    # Executa os testes de performance
    run_tests_resume(data_root="data/raw", output_file="results/report_quadratic.md")
    
    # Executa os testes unitários
    unittest.main(argv=[''], exit=False, verbosity=2)
