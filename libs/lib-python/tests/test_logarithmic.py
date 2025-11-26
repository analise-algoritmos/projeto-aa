import unittest
import time
import os
import math
from src.logarithmic import merge_sort, quicksort, heapsort, introsort, timsort, slowsort, linear_sort, cubesort, mergeSortInPlace,\
    tournament_sort, tree_sort, block_sort, patienceSorting, smooth_sort

# Caminho robusto até o arquivo de massa
BASE_DIR = os.path.dirname(__file__)
MASSA_PATH = os.path.abspath(os.path.join(BASE_DIR, "..", "..", "..", "data", "massa.txt"))

def ler_massa(path):
    with open(path, "r") as f:
        lines = f.readlines()

    massa = []
    tipo = None
    for line in lines:
        line = line.strip()
        if not line:
            continue
        if line.startswith("#"):
            tipo = line[1:]  # 'int' ou 'float'
            continue
        arr = [float(x) if '.' in x else int(x) for x in line.split()]
        massa.append((tipo, arr))
    return massa


class TestLogarithmicSorts(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.massa = ler_massa(MASSA_PATH)

    def test_algoritmos_logaritmicos(self):
        resultados = {
            "Merge Sort": [],
            "Quick Sort": [],
            "Heap Sort": [],
            "Intro Sort": [],
            "Tim Sort": [],
            "Slow Sort": [],
            "Linear Sort": [],
            "Cube Sort": [],
            "Merge Sort InPlace":[],
            "Tournament Sort": [],
            "Tree Sort": [],
            "Block Sort": [],
            "Patience Sorting":[],
            "Smooth Sort":[]
        }

        for idx, (tipo, arr) in enumerate(self.massa, start=1):
            # testamos apenas inteiros (float pode ser usado em Merge/Tim)
            if not arr:
                continue

            # Merge Sort
            a = arr.copy()
            inicio = time.time()
            merge_sort(a)
            tempo = time.time() - inicio
            resultados["Merge Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Quick Sort
            inicio = time.time()
            result = quicksort(arr.copy())
            tempo = time.time() - inicio
            resultados["Quick Sort"].append((idx, result == sorted(arr), len(arr), tempo))

            # Heap Sort
            a = arr.copy()
            inicio = time.time()
            heapsort(a)
            tempo = time.time() - inicio
            resultados["Heap Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Intro Sort
            a = arr.copy()
            inicio = time.time()
            introsort(a)
            tempo = time.time() - inicio
            resultados["Intro Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Tim Sort
            a = arr.copy()
            inicio = time.time()
            timsort(a)
            tempo = time.time() - inicio
            resultados["Tim Sort"].append((idx, a == sorted(arr), len(arr), tempo))
            
            # Slow Sort
            a = arr.copy()
            inicio = time.time()
            slowsort(a, 0, len(arr) - 1)
            tempo = time.time() - inicio
            resultados["Slow Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Linear Sort
            a = arr.copy()
            inicio = time.time()
            linear_sort(a)
            tempo = time.time() - inicio
            resultados["Linear Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Cube Sort
            a = arr.copy()
            inicio = time.time()
            cubesort(a)
            tempo = time.time() - inicio
            resultados["Cube Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Merge Sort In-Place
            a = arr.copy()
            inicio = time.time()
            mergeSortInPlace(a, 0, len(arr) - 1)
            tempo = time.time() - inicio
            resultados["Merge Sort InPlace"].append((idx, a == sorted(arr), len(arr), tempo))

            # Tournament Sort
            a = arr.copy()
            inicio = time.time()
            tournament_sort(a)
            tempo = time.time() - inicio
            resultados["Tournament Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Tree Sort
            a = arr.copy()
            inicio = time.time()
            tree_sort(a)
            tempo = time.time() - inicio
            resultados["Tree Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Block Sort
            a = arr.copy()
            inicio = time.time()
            block_sort(a, (int(math.sqrt(len(a)))))
            tempo = time.time() - inicio
            resultados["Block Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Patience Sorting 
            a = arr.copy()
            inicio = time.time()
            patienceSorting(a)
            tempo = time.time() - inicio
            resultados["Patience Sorting"].append((idx, a == sorted(arr), len(arr), tempo))

            # Smooth Sort
            a = arr.copy()
            inicio = time.time()
            smooth_sort(a)
            tempo = time.time() - inicio
            resultados["Smooth Sort"].append((idx, a == sorted(arr), len(arr), tempo))

        # Saída formatada
        for nome, resultados_lista in resultados.items():
            print(f"\n=== {nome} ===")
            for massa_id, ok, tam, tempo in resultados_lista:
                status = "OK" if ok else "FALHA"
                print(f"Massa {massa_id}: {status}, tamanho={tam}, tempo={tempo:.6f}s")


if __name__ == "__main__":
    unittest.main()
