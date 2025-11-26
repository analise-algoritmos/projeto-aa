import os
import sys
import time
from pathlib import Path
from typing import List
import re
from datetime import datetime
import statistics

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../src")))

from linear import (
    counting_sort,
    pigeonhole_sort,
    bucket_sort_uniform,
    bucket_sort_integer,
    lsd_radix_sort,
    spreadsort,
    burstsort,
    flashsort,
    postman_sort,
    bead_sort
)

algorithms = [
    ("Counting Sort", counting_sort),
    ("Pigeonhole Sort", pigeonhole_sort),
    ("Bucket Sort Uniform", bucket_sort_uniform),
    ("Bucket Sort Integer", bucket_sort_integer),
    ("LSD Radix Sort", lsd_radix_sort),
    ("Spreadsort", spreadsort),
    ("Burstsort", burstsort),
    ("Flashsort", flashsort),
    ("Postman Sort", postman_sort),
    ("Bead Sort", bead_sort),
]


def is_sorted(arr: List[float]) -> bool:
    return all(arr[i] <= arr[i + 1] for i in range(len(arr) - 1))


# ------------------------
# Lê linhas existentes do relatório para saber onde parou
# ------------------------
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
                if file_path:
                    processed.add((algo_name, file_path))
    return processed


# ------------------------
# Processa um arquivo e escreve no relatório
# ------------------------
def process_file(file_path: Path, f_out, processed_entries, repetitions=10):

    start_processing_time = datetime.now()
    print(f"[INFO] Início do processamento de {file_path} às {start_processing_time.strftime('%Y-%m-%d %H:%M:%S')}")

    # ---- leitura dos dados ----
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
        print(f"[ERRO] Não foi possível ler {file_path}: {e}")
        return

    if not data:
        print("[AVISO] Arquivo vazio ou ilegível:", file_path)
        return

    dtype = 'int' if all(x.is_integer() for x in data) else 'float'
    min_val = min(data)
    max_val = max(data)

    # --------------------------
    # Execução dos algoritmos
    # --------------------------
    for algo_name, algo_func in algorithms:

        # já registrado?
        if (algo_name, str(file_path)) in processed_entries:
            continue

        print(f"  - Executando {algo_name}...")

        times = []

        # bead sort só funciona com inteiros
        if algo_name == "Bead Sort":
            data_used = [int(x) for x in data]
            estimated_size = len(data_used) * max(data_used)
            if estimated_size > 10_000_000:
                print(f"[AVISO] Bead Sort ignorado (estimativa muito grande).")
                continue
        else:
            data_used = data

        # repetições
        for _ in range(repetitions):
            arr_copy = list(data_used)
            start = time.time()
            algo_func(arr_copy)
            end = time.time()
            times.append(end - start)

        media = statistics.mean(times)
        desvio = statistics.stdev(times) if len(times) > 1 else 0.0

        # registrar
        f_out.write(
            f"| {algo_name} | {file_path} | {len(data)} | {dtype} | {min_val} | {max_val} | {media:.6f} | {desvio:.6f} |\n"
        )
        f_out.flush()

        processed_entries.add((algo_name, str(file_path)))

    del data


# ------------------------
# Execução principal
# ------------------------
def run_tests_resume(data_root="data/raw", output_file="results/report_linear.md"):
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    root_path = Path(data_root)

    # ⬇⬇⬇ SOMENTE uniformInt/*.txt
    txt_files = [
        p for p in root_path.rglob("*.txt")
        if "uniformInt" in str(p)
    ]

    print(f"Arquivos encontrados (uniformInt): {len(txt_files)}")

    processed_entries = load_processed_entries(output_file)
    print(f"Entradas já processadas: {len(processed_entries)}")

    if not os.path.exists(output_file):
        with open(output_file, "w", encoding="utf-8") as f_out:
            f_out.write("# Relatório de Testes de Algoritmos Lineares\n\n")
            f_out.write("| Algoritmo | Arquivo | Tamanho | Tipo | Min | Max | Média (s) | Desvio Padrão |\n")
            f_out.write("|-----------|---------|---------|------|-----|-----|------------|----------------|\n")

    with open(output_file, "a", encoding="utf-8") as f_out:
        for file_path in txt_files:
            print(f"\nProcessando arquivo: {file_path}")
            process_file(file_path, f_out, processed_entries, repetitions=10)

    print(f"\nRelatório atualizado: {output_file}")


if __name__ == "__main__":
    run_tests_resume(data_root="data/raw", output_file="results/report_linear.md")
