# tests/test_linear.py
import os
import sys
import time
from pathlib import Path
from typing import List
import re
from datetime import datetime

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
                file_path = parts[2].strip()
                algo_name = parts[1].strip()
                if file_path:
                    processed.add((algo_name, file_path))
    return processed

# ------------------------
# Processa um arquivo e escreve no relatório
# ------------------------
def process_file(file_path: Path, f_out, last_algorithm_dict, processed_entries):
    # --- NOVO: log do início do processamento ---
    start_processing_time = datetime.now()
    print(f"[INFO] Início do processamento de {file_path}: {start_processing_time.strftime('%Y-%m-%d %H:%M:%S')}")

    data = []
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                numbers = re.findall(r"[-+]?\d*\.\d+|[-+]?\d+", line)
                for num in numbers:
                    try:
                        data.append(float(num))
                    except ValueError:
                        continue
    except Exception as e:
        print(f"[ERRO] Não foi possível ler {file_path}: {e}")
        return

    if not data:
        return

    dtype = 'int' if all(x.is_integer() for x in data) else 'float'
    min_val = min(data)
    max_val = max(data)

    for algo_name, algo_func in algorithms:
        # Pula se já processado
        if (algo_name, str(file_path)) in processed_entries:
            continue

        if algo_name == "Bead Sort":
            array_to_sort = [int(x) for x in data]

            # --- NOVO: checagem de tamanho para evitar MemoryError ---
            estimated_size = len(array_to_sort) * (max(array_to_sort) if array_to_sort else 0)
            if estimated_size > 10_000_000:  # limite ajustável
                print(f"[AVISO] Arquivo {file_path} muito grande para Bead Sort, pulando...")
                continue
        else:
            array_to_sort = data

        start = time.time()
        sorted_array = algo_func(array_to_sort)
        end = time.time()

        algo_name_to_write = algo_name if last_algorithm_dict.get('last') != algo_name else ""
        last_algorithm_dict['last'] = algo_name

        f_out.write(f"| {algo_name_to_write} | {file_path} | {len(data)} | {dtype} | {min_val} | {max_val} | {end - start:.6f} |\n")
        f_out.flush()

        del array_to_sort
        del sorted_array

    del data

# ------------------------
# Execução principal
# ------------------------
def run_tests_resume(data_root="data/raw", output_file="results/report_linear.md"):
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    root_path = Path(data_root)
    txt_files = list(root_path.rglob("*.txt"))
    print(f"Arquivos encontrados: {len(txt_files)}")

    processed_entries = load_processed_entries(output_file)
    print(f"Entradas já processadas: {len(processed_entries)}")

    # Se arquivo não existe, escreve cabeçalho
    if not os.path.exists(output_file):
        f_out = open(output_file, "w", encoding="utf-8")
        f_out.write("# Relatório de Testes de Algoritmos Lineares\n\n")
        f_out.write("| Algoritmo | Arquivo | Tamanho | Tipo de dado | Min | Max | Tempo (s) |\n")
        f_out.write("|-----------|---------|---------|--------------|-----|-----|-----------|\n")
        f_out.close()

    last_algorithm_dict = {'last': None}
    with open(output_file, "a", encoding="utf-8") as f_out:
        for file_path in txt_files:
            print(f"\nProcessando arquivo: {file_path}")
            process_file(file_path, f_out, last_algorithm_dict, processed_entries)

    print(f"\nRelatório atualizado: {output_file}")

# ------------------------
# Execução
# ------------------------
if __name__ == "__main__":
    run_tests_resume(data_root="data/raw", output_file="results/report_linear.md")
