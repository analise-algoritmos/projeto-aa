import unittest
import time
import os
from src.linear import counting_sort, radix_sort, bucket_sort

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

class TestLinearSorts(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.massa = ler_massa(MASSA_PATH)

    def test_algoritmos_por_algoritmo(self):
        resultados = {
            "Counting Sort": [],
            "Radix Sort": [],
            "Bucket Sort": []
        }

        for idx, (tipo, arr) in enumerate(self.massa, start=1):
            if tipo == "int":
                # Counting Sort
                inicio = time.time()
                result = counting_sort(arr.copy(), max(arr) if arr else 0)
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Counting Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Radix Sort
                inicio = time.time()
                result = radix_sort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Radix Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

            elif tipo == "float":
                # Bucket Sort
                inicio = time.time()
                result = bucket_sort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Bucket Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

        # Exibe resultados organizados por algoritmo
        for alg, res_list in resultados.items():
            print(f"\n=== {alg} ===")
            for res in res_list:
                status = "OK" if res["correto"] else "FALHA"
                print(f"Massa {res['massa']}: {status}, tamanho={res['tamanho']}, tempo={res['tempo']:.6f}s")


if __name__ == "__main__":
    unittest.main()
