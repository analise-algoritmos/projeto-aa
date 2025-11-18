import unittest
import time
import os
from src.logarithmic import merge_sort, quicksort, heapsort, introsort, timsort, slowsort, linear_sort

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
            "Linear Sort": []
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

        # Saída formatada
        for nome, resultados_lista in resultados.items():
            print(f"\n=== {nome} ===")
            for massa_id, ok, tam, tempo in resultados_lista:
                status = "OK" if ok else "FALHA"
                print(f"Massa {massa_id}: {status}, tamanho={tam}, tempo={tempo:.6f}s")


if __name__ == "__main__":
    unittest.main()
