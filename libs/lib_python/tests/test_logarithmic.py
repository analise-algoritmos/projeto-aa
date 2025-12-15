import unittest
import time
import os
import math
from src.logarithmic import merge_sort, quicksort, fluxsort, crumsort, library_sort, msd_radix_sort, msd_radix_sort_in_place, merge_insertion_sort, heapsort, introsort, timsort, slowsort, linear_sort, cubesort, mergeSortInPlace,\
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
            "Flux Sort": [],
            "Crumb Sort": [],
            "Library Sort": [],
            "MSD Radix Sort": [],
            "MSD Radix Sort In-Place": [],
            "Merge Insertion Sort": [],
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

            # Flux Sort
            inicio = time.time()
            result = fluxsort(arr.copy())
            tempo = time.time() - inicio
            resultados["Flux Sort"].append((idx, result == sorted(arr), len(arr), tempo))

            # Crumb Sort
            inicio = time.time()
            result = crumsort(arr.copy())
            tempo = time.time() - inicio
            resultados["Crumb Sort"].append((idx, result == sorted(arr), len(arr), tempo))

            # Library Sort
            inicio = time.time()
            result = library_sort(arr.copy())
            tempo = time.time() - inicio
            resultados["Library Sort"].append((idx, result == sorted(arr), len(arr), tempo))

            # MSD Radix Sort
            inicio = time.time()
            result = msd_radix_sort(arr.copy())
            tempo = time.time() - inicio
            resultados["MSD Radix Sort"].append((idx, result == sorted(arr), len(arr), tempo))

            # MSD Radix Sort In-Place
            a = arr.copy()
            inicio = time.time()
            msd_radix_sort_in_place(a)
            tempo = time.time() - inicio
            resultados["MSD Radix Sort In-Place"].append((idx, a == sorted(arr), len(arr), tempo))

            # Merge Insertion Sort
            inicio = time.time()
            result = merge_insertion_sort(arr.copy())
            tempo = time.time() - inicio
            resultados["Merge Insertion Sort"].append((idx, result == sorted(arr), len(arr), tempo))

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

    def test_fluxsort_basico(self):
        """Testa casos básicos do fluxsort"""
        # Array vazio
        self.assertEqual(fluxsort([]), [])
        
        # Array com um elemento
        self.assertEqual(fluxsort([1]), [1])
        
        # Array já ordenado
        arr = [1, 2, 3, 4, 5]
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))
        
        # Array reverso
        arr = [5, 4, 3, 2, 1]
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))
        
        # Array com elementos duplicados
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))
        
        # Array pequeno (<=16 elementos) - deve usar sorted()
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6, 10, 11, 12, 13, 14, 15, 16]
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))
        
        # Array grande (>16 elementos)
        arr = list(range(100, 0, -1))
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))
        
        # Array com números negativos
        arr = [-5, 3, -1, 0, 2, -3, 1]
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))
        
        # Array com floats
        arr = [3.5, 1.2, 4.8, 2.1, 5.9]
        self.assertEqual(fluxsort(arr.copy()), sorted(arr))

    def test_crumsort_basico(self):
        """Testa casos básicos do crumsort"""
        # Array vazio
        self.assertEqual(crumsort([]), [])
        
        # Array com um elemento
        self.assertEqual(crumsort([1]), [1])
        
        # Array já ordenado
        arr = [1, 2, 3, 4, 5]
        self.assertEqual(crumsort(arr.copy()), sorted(arr))
        
        # Array reverso
        arr = [5, 4, 3, 2, 1]
        self.assertEqual(crumsort(arr.copy()), sorted(arr))
        
        # Array com elementos duplicados
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        self.assertEqual(crumsort(arr.copy()), sorted(arr))
        
        # Array pequeno (<=16 elementos) - deve usar sorted()
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6, 10, 11, 12, 13, 14, 15, 16]
        self.assertEqual(crumsort(arr.copy()), sorted(arr))
        
        # Array grande (>16 elementos)
        arr = list(range(100, 0, -1))
        self.assertEqual(crumsort(arr.copy()), sorted(arr))
        
        # Array com números negativos
        arr = [-5, 3, -1, 0, 2, -3, 1]
        self.assertEqual(crumsort(arr.copy()), sorted(arr))
        
        # Array com floats
        arr = [3.5, 1.2, 4.8, 2.1, 5.9]
        self.assertEqual(crumsort(arr.copy()), sorted(arr))

    def test_library_sort_basico(self):
        """Testa casos básicos do library_sort"""
        # Array vazio
        self.assertEqual(library_sort([]), [])
        
        # Array com um elemento
        self.assertEqual(library_sort([1]), [1])
        
        # Array já ordenado
        arr = [1, 2, 3, 4, 5]
        self.assertEqual(library_sort(arr.copy()), sorted(arr))
        
        # Array reverso
        arr = [5, 4, 3, 2, 1]
        self.assertEqual(library_sort(arr.copy()), sorted(arr))
        
        # Array com elementos duplicados
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        self.assertEqual(library_sort(arr.copy()), sorted(arr))
        
        # Array pequeno
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
        self.assertEqual(library_sort(arr.copy()), sorted(arr))
        
        # Array grande
        arr = list(range(100, 0, -1))
        self.assertEqual(library_sort(arr.copy()), sorted(arr))
        
        # Array com números negativos
        arr = [-5, 3, -1, 0, 2, -3, 1]
        self.assertEqual(library_sort(arr.copy()), sorted(arr))
        
        # Array com floats
        arr = [3.5, 1.2, 4.8, 2.1, 5.9]
        self.assertEqual(library_sort(arr.copy()), sorted(arr))

    def test_msd_radix_sort_basico(self):
        """Testa casos básicos do msd_radix_sort"""
        # Array vazio
        self.assertEqual(msd_radix_sort([]), [])
        
        # Array com um elemento
        self.assertEqual(msd_radix_sort([1]), [1])
        
        # Array já ordenado
        arr = [1, 2, 3, 4, 5]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array reverso
        arr = [5, 4, 3, 2, 1]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array com elementos duplicados
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array pequeno
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array grande
        arr = list(range(100, 0, -1))
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array com números de diferentes tamanhos
        arr = [1, 10, 100, 2, 20, 200, 3, 30, 300]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array com números grandes
        arr = [12345, 67890, 11111, 99999, 54321]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))
        
        # Array com números de um dígito
        arr = [9, 1, 5, 3, 7, 2, 8, 4, 6]
        self.assertEqual(msd_radix_sort(arr.copy()), sorted(arr))

    def test_msd_radix_sort_in_place_basico(self):
        """Testa casos básicos do msd_radix_sort_in_place"""
        # Array vazio
        arr = []
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, [])
        
        # Array com um elemento
        arr = [1]
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, [1])
        
        # Array já ordenado
        arr = [1, 2, 3, 4, 5]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array reverso
        arr = [5, 4, 3, 2, 1]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array com elementos duplicados
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array pequeno
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array grande
        arr = list(range(100, 0, -1))
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array com números de diferentes tamanhos
        arr = [1, 10, 100, 2, 20, 200, 3, 30, 300]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array com números grandes
        arr = [12345, 67890, 11111, 99999, 54321]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Array com números de um dígito
        arr = [9, 1, 5, 3, 7, 2, 8, 4, 6]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr)
        self.assertEqual(arr, expected)
        
        # Teste com parâmetros customizados
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
        expected = sorted(arr.copy())
        msd_radix_sort_in_place(arr, ini=2, fim=7)
        # Verifica que apenas o subarray foi ordenado
        self.assertEqual(arr[2:7], sorted(arr[2:7]))

    def test_merge_insertion_sort_basico(self):
        """Testa casos básicos do merge_insertion_sort"""
        # Array vazio
        self.assertEqual(merge_insertion_sort([]), [])
        
        # Array com um elemento
        self.assertEqual(merge_insertion_sort([1]), [1])
        
        # Array já ordenado
        arr = [1, 2, 3, 4, 5]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array reverso
        arr = [5, 4, 3, 2, 1]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array com elementos duplicados
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array pequeno
        arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array grande
        arr = list(range(100, 0, -1))
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array com números negativos
        arr = [-5, 3, -1, 0, 2, -3, 1]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array com floats
        arr = [3.5, 1.2, 4.8, 2.1, 5.9]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array com tamanho par
        arr = [4, 2, 8, 1, 6, 3]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))
        
        # Array com tamanho ímpar
        arr = [4, 2, 8, 1, 6]
        self.assertEqual(merge_insertion_sort(arr.copy()), sorted(arr))


if __name__ == "__main__":
    unittest.main()
