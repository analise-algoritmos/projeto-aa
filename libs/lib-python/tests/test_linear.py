import unittest
import time
import os
from src.linear import counting_sort, radix_sort, bucket_sort, spreadsort, burstsort, flashsort, postman_sort, bead_sort, pigeonhole_sort, bucket_sort_whole_keys

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

class TestLinearSorts(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.massa = ler_massa(MASSA_PATH)

    def test_algoritmos_por_algoritmo(self):
        resultados = {
            "Counting Sort": [],
            "Radix Sort": [],
            "Bucket Sort": [],
            "Spread Sort": [],
            "Burst Sort": [],
            "Flash Sort": [],
            "Postman Sort": [],
            "Bead Sort": [],
            "Pigeonhole Sort": [],
            "Bucket Sort Whole Keys": []
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

                # Spread Sort
                inicio = time.time()
                result = spreadsort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Spread Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Burst Sort (converte para strings)
                arr_str = [str(x) for x in arr]
                inicio = time.time()
                result = burstsort(arr_str.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr_str)
                resultados["Burst Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Flash Sort
                inicio = time.time()
                result = flashsort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Flash Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Postman Sort
                inicio = time.time()
                result = postman_sort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Postman Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Bead Sort (apenas inteiros não-negativos)
                if all(x >= 0 for x in arr):
                    inicio = time.time()
                    result = bead_sort(arr.copy())
                    duracao = time.time() - inicio
                    correto = result == sorted(arr)
                    resultados["Bead Sort"].append({
                        "massa": idx,
                        "correto": correto,
                        "tamanho": len(arr),
                        "tempo": duracao
                    })

                # Pigeonhole Sort
                inicio = time.time()
                result = pigeonhole_sort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Pigeonhole Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Bucket Sort Whole Keys
                inicio = time.time()
                result = bucket_sort_whole_keys(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Bucket Sort Whole Keys"].append({
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

                # Spread Sort
                inicio = time.time()
                result = spreadsort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Spread Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Burst Sort (converte para strings)
                arr_str = [str(x) for x in arr]
                inicio = time.time()
                result = burstsort(arr_str.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr_str)
                resultados["Burst Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Flash Sort
                inicio = time.time()
                result = flashsort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Flash Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Postman Sort
                inicio = time.time()
                result = postman_sort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Postman Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Pigeonhole Sort
                inicio = time.time()
                result = pigeonhole_sort(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Pigeonhole Sort"].append({
                    "massa": idx,
                    "correto": correto,
                    "tamanho": len(arr),
                    "tempo": duracao
                })

                # Bucket Sort Whole Keys
                inicio = time.time()
                result = bucket_sort_whole_keys(arr.copy())
                duracao = time.time() - inicio
                correto = result == sorted(arr)
                resultados["Bucket Sort Whole Keys"].append({
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
