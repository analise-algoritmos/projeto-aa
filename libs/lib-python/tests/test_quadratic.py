import unittest
import time
import os
from src import quadratic

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
            "Pancake Sort": [],
            "Bitonic Sort": [],
            "Cocktail Shaker Sort": [],
            "Strand Sort": [],
            "Exchange Sort": [],
            "Cycle Sort": [],
            "Recombinant Sort": [],
            "ICBICS": [],
            "Spaghetti Sort": [],
            "Sorting Network": []
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
                "Pancake Sort": quadratic.pancake_sort,
                "Bitonic Sort": quadratic.bitonic_sort,
                "Cocktail Shaker Sort": quadratic.cocktail_shaker_sort,
                "Exchange Sort": quadratic.exchange_sort,
                "Cycle Sort": quadratic.cycle_sort,
                "Recombinant Sort": quadratic.recombinant_sort,
                "ICBICS": quadratic.icbics
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

            # Strand Sort retorna uma nova lista ordenada
            inicio = time.time()
            resultado_strand = quadratic.strand_sort(arr)
            duracao = time.time() - inicio
            correto = resultado_strand == sorted(arr)
            resultados["Strand Sort"].append({
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
