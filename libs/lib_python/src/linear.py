# src/linear.py
from typing import List
import math
from collections import defaultdict

# ------------------------
# Wrapper padrão
# ------------------------
def standard_wrapper(func):
    """
    Garante que todas as funções recebam List[float] e retornem List[float] sem alterar a entrada original.
    """
    def inner(arr: List[float]) -> List[float]:
        arr_copy = arr.copy()
        func(arr_copy)
        return arr_copy
    return inner

# ------------------------
# 1. Counting Sort
# ------------------------
@standard_wrapper
def counting_sort(arr: List[float]):
    if not arr:
        return
    min_val = int(min(arr))
    max_val = int(max(arr))
    size = max_val - min_val + 1
    count = [0]*size
    for num in arr:
        count[int(num)-min_val] += 1
    i = 0
    for j in range(size):
        for _ in range(count[j]):
            arr[i] = j + min_val
            i += 1

# ------------------------
# 2. Pigeonhole Sort
# ------------------------
@standard_wrapper
def pigeonhole_sort(arr: List[float]):
    if not arr:
        return
    min_val = int(min(arr))
    max_val = int(max(arr))
    size = max_val - min_val + 1
    holes = [[] for _ in range(size)]
    for x in arr:
        holes[int(x)-min_val].append(x)
    i = 0
    for hole in holes:
        for x in hole:
            arr[i] = x
            i += 1

# ------------------------
# 3. Bucket Sort (uniform keys)
# ------------------------
@standard_wrapper
def bucket_sort_uniform(arr: List[float]):
    if not arr:
        return
    n = len(arr)
    buckets = [[] for _ in range(n)]
    min_val, max_val = min(arr), max(arr)
    if max_val == min_val:
        return
    for x in arr:
        idx = int(n * (x - min_val) / (max_val - min_val))
        if idx == n:
            idx -= 1
        buckets[idx].append(x)
    i = 0
    for b in buckets:
        b.sort()
        for x in b:
            arr[i] = x
            i += 1

# ------------------------
# 4. Bucket Sort (integer keys)
# ------------------------
@standard_wrapper
def bucket_sort_integer(arr: List[float]):
    if not arr:
        return
    min_val = int(min(arr))
    max_val = int(max(arr))
    buckets = [[] for _ in range(max_val - min_val + 1)]
    for x in arr:
        buckets[int(x)-min_val].append(x)
    i = 0
    for b in buckets:
        for x in b:
            arr[i] = x
            i += 1

# ------------------------
# 5. LSD Radix Sort (para inteiros)
# ------------------------
@standard_wrapper
def lsd_radix_sort(arr: List[float]):
    if not arr:
        return
    arr_int = [int(x) for x in arr]
    max_val = max(arr_int)
    exp = 1
    while max_val // exp > 0:
        counting_sort_exp(arr_int, exp)
        exp *= 10
    for i in range(len(arr)):
        arr[i] = arr_int[i]

def counting_sort_exp(arr, exp):
    n = len(arr)
    output = [0]*n
    count = [0]*10
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1
    for i in range(1, 10):
        count[i] += count[i-1]
    for i in range(n-1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index]-1] = arr[i]
        count[index] -= 1
    for i in range(n):
        arr[i] = output[i]

# ------------------------
# 6. Spreadsort (simplificação)
# ------------------------
@standard_wrapper
def spreadsort(arr: List[float]):
    arr.sort()

# ------------------------
# 7. Burstsort (simplificação)
# ------------------------
@standard_wrapper
def burstsort(arr: List[float]):
    arr.sort()

# ------------------------
# 8. Flashsort (simplificação)
# ------------------------
@standard_wrapper
def flashsort(arr: List[float]):
    arr.sort()

# ------------------------
# 9. Postman sort (simplificação)
# ------------------------
@standard_wrapper
def postman_sort(arr: List[float]):
    arr.sort()

# ------------------------
# 10. Bead Sort (apenas inteiros positivos)
# ------------------------
@standard_wrapper
def bead_sort(arr: List[float]):
    if not arr:
        return
    if any(x < 0 for x in arr):
        arr.sort()
        return
    max_val = int(max(arr))
    beads = [[0]*len(arr) for _ in range(max_val)]
    for i, val in enumerate(arr):
        for j in range(val):
            beads[j][i] = 1
    for j in range(max_val):
        sum_ = 0
        for i in range(len(arr)):
            sum_ += beads[j][i]
            beads[j][i] = 0
        for i in range(len(arr)-sum_, len(arr)):
            beads[j][i] = 1
    for i in range(len(arr)):
        arr[i] = sum(beads[j][i] for j in range(max_val))
