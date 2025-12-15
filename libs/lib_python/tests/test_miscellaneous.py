import unittest
import time
import os
from src.miscellaneous import stoogesort, bogo_sort

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
            "Stooge Sort": [],
            "Bogo Sort": []
        }

        for idx, (tipo, arr) in enumerate(self.massa, start=1):
            # testamos apenas inteiros (float pode ser usado em Merge/Tim)
            if not arr:
                continue

            # Stooge Sort
            a = arr.copy()
            inicio = time.time()
            stoogesort(a, 0, len(arr) - 1)
            tempo = time.time() - inicio
            resultados["Stooge Sort"].append((idx, a == sorted(arr), len(arr), tempo))

            # Bogo Sort
            a = arr.copy()
            inicio = time.time()
            bogo_sort(a)
            tempo = time.time() - inicio
            resultados["Bogo Sort"].append((idx, a == sorted(arr), len(arr), tempo))

        # Saída formatada
        for nome, resultados_lista in resultados.items():
            print(f"\n=== {nome} ===")
            for massa_id, ok, tam, tempo in resultados_lista:
                status = "OK" if ok else "FALHA"
                print(f"Massa {massa_id}: {status}, tamanho={tam}, tempo={tempo:.6f}s")


if __name__ == "__main__":
    unittest.main()
