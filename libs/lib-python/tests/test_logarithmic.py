import os
import sys
import time
import statistics
from pathlib import Path
from typing import List
import re
from datetime import datetime

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../src")))

from logarithmic import (
    quicksort,
    merge_sort,
    heapsort,
    introsort,
    timsort,
    slowsort,
    cubesort,
    mergeSortInPlace,
    tournament_sort,
    tree_sort,
    block_sort,
    patienceSorting,
    smooth_sort
)


# ============================================================
# Lista de algoritmos Logarítmicos (ou n log n)
# ============================================================
algorithms = [
    ("Quicksort", quicksort),
    ("Merge Sort", merge_sort),
    ("Heapsort", heapsort),
    ("Introsort", introsort),
    ("Timsort", timsort),
    # ("Slowsort", slowsort),
    ("CubeSort", cubesort),
    ("In-Place MergeSort", mergeSortInPlace),
    ("Tournament Sort", tournament_sort),
    ("Tree Sort", tree_sort),
    ("Block Sort", lambda arr: block_sort(arr, block_size=max(1, int(len(arr)**0.5)))),
    ("Patience Sorting", patienceSorting),
    ("Smooth Sort", smooth_sort),
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

    print(f"[INFO] Início do processamento do arquivo {file_path} em: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

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
            try:
                result = algo_func(arr_copy)
            except:
                result = None
            end = time.time()
            times.append(end - start)

        media = statistics.mean(times)
        desvio = statistics.stdev(times) if len(times) > 1 else 0.0

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
def run_tests_resume(data_root="data/raw", output_file="results/report_logarithmic.md"):

    print("\n============================================")
    print("📌 INÍCIO DOS TESTES LOGARÍTMICOS (n log n)")
    print("============================================\n")

    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    root_path = Path(data_root)

    txt_files = [
        p for p in root_path.rglob("*.txt")
        if "uniformInt" in str(p)
    ]

    print(f"Arquivos encontrados (uniformInt): {len(txt_files)}")

    processed_entries = load_processed_entries(output_file)
    print(f"Entradas já processadas: {len(processed_entries)}")

    if not os.path.exists(output_file):
        with open(output_file, "w", encoding="utf-8") as f_out:
            f_out.write("# Relatório de Testes de Algoritmos Logarítmicos (n log n)\n\n")
            f_out.write("| Algoritmo | Arquivo | Tamanho | Tipo | Min | Max | Média (s) | Desvio Padrão |\n")
            f_out.write("|-----------|---------|---------|------|-----|-----|------------|----------------|\n")

    with open(output_file, "a", encoding="utf-8") as f_out:
        for file_path in txt_files:
            process_file(file_path, f_out, processed_entries, repetitions=10)

    print("\n============================================")
    print("🏁 FIM DOS TESTES")
    print(f"📄 Relatório salvo em: {output_file}")
    print("============================================\n")


if __name__ == "__main__":
    run_tests_resume(
        data_root="data/raw",
        output_file="results/report_logarithmic.md"
    )
