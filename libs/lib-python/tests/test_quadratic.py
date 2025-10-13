import unittest
import time
import os
from src import quadratic

MASSA_PATH = os.path.join("C:/Users/User/Desktop/code/aa/projeto-aa/data/massa.txt")

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


class TestQuadraticSorts(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.massa = ler_massa(MASSA_PATH)

    def test_algoritmos_quadraticos(self):
        resultados = {
            "Bubble Sort": [],
            "Insertion Sort": [],
            "Comb Sort": [],
            "Selection Sort": [],
            "Shell Sort": [],
            "Gnome Sort": [],
            "Shaker Sort": [],
            "Odd-Even Sort": [],
            "Pancake Sort": []
        }

        for idx, (tipo, arr) in enumerate(self.massa, start=1):
            if tipo != "int":
                # algoritmos quadráticos são aplicáveis apenas para inteiros
                continue

            algoritmos = {
                "Bubble Sort": quadratic.bubble_sort,
                "Insertion Sort": quadratic.insertion_sort,
                "Comb Sort": quadratic.comb_sort,
                "Selection Sort": quadratic.selection_sort,
                "Shell Sort": quadratic.shell_sort,
                "Gnome Sort": quadratic.gnome_sort,
                "Shaker Sort": quadratic.shaker_sort,
                "Odd-Even Sort": quadratic.odd_even_sort,
                "Pancake Sort": quadratic.pancake_sort
            }

            for nome, func in algoritmos.items():
                dados = arr.copy()
                inicio = time.time()
                func(dados)
                duracao = time.time() - inicio
                correto = dados == sorted(arr)
                resultados[nome].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

        # Exibe resultados detalhados
        for alg, res_list in resultados.items():
            print(f"\n=== {alg} ===")
            for res in res_list:
                status = "OK" if res["correto"] else "FALHA"
                print(f"Massa {res['massa']}: {status}, tamanho={res['tamanho']}, tempo={res['tempo']:.6f}s")


if __name__ == "__main__":
    unittest.main()
