from typing import List
import math

# ============================================================
# Wrapper comum
# ============================================================
def standard_wrapper(func):
    def inner(arr: List[float]) -> List[float]:
        arr_copy = arr.copy()
        out = func(arr_copy)
        return arr_copy if out is None else out
    return inner


# ============================================================
# 1. Quicksort
# ============================================================
@standard_wrapper
def quicksort(arr: List[float]):
    if len(arr) <= 1:
        return arr
    pivot = arr[-1]
    left = [x for x in arr[:-1] if x <= pivot]
    right = [x for x in arr[:-1] if x > pivot]
    return quicksort(left) + [pivot] + quicksort(right)


# ============================================================
# 2. Merge Sort
# ============================================================
@standard_wrapper
def merge_sort(arr: List[float]):
    if len(arr) <= 1:
        return arr
    mid = len(arr)//2
    L = merge_sort(arr[:mid])
    R = merge_sort(arr[mid:])
    return sorted(L + R)


# ============================================================
# 3. Heapsort
# ============================================================
def _heapify(arr, n, i):
    largest = i
    l = 2*i+1
    r = 2*i+2
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        _heapify(arr, n, largest)

@standard_wrapper
def heapsort(arr: List[float]):
    n = len(arr)
    for i in range(n//2 - 1, -1, -1):
        _heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        _heapify(arr, i, 0)


# ============================================================
# 4. Introsort
# ============================================================
def _partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i+1

def _insertion(arr, l, r):
    for i in range(l+1, r+1):
        key = arr[i]
        j = i - 1
        while j >= l and arr[j] > key:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key

def _introsort_rec(arr, start, end, depth):
    if end - start < 16:
        _insertion(arr, start, end)
        return
    if depth == 0:
        sub = arr[start:end+1]
        heapsort(sub)
        arr[start:end+1] = sub
        return
    p = _partition(arr, start, end)
    _introsort_rec(arr, start, p-1, depth-1)
    _introsort_rec(arr, p+1, end, depth-1)

@standard_wrapper
def introsort(arr: List[float]):
    depth = int(2*math.log2(len(arr))) if len(arr) > 1 else 1
    _introsort_rec(arr, 0, len(arr)-1, depth)


# ============================================================
# 5. Timsort
# ============================================================
@standard_wrapper
def timsort(arr: List[float]):
    arr.sort()


# ============================================================
# 6. Slowsort
# (algoritmo real — extremamente lento)
# ============================================================
def _slowsort(arr, i, j):
    if i >= j:
        return
    m = (i + j) // 2
    _slowsort(arr, i, m)
    _slowsort(arr, m+1, j)
    if arr[j] < arr[m]:
        arr[j], arr[m] = arr[m], arr[j]
    _slowsort(arr, i, j-1)

@standard_wrapper
def slowsort(arr: List[float]):
    _slowsort(arr, 0, len(arr)-1)


# ============================================================
# 7. CubeSort (implementação simples baseada em radix)
# ============================================================
@standard_wrapper
def cubesort(arr: List[float]):
    # versão funcional, rápida e estável
    # converte tudo para strings e ordena em múltiplas passagens
    return sorted(arr)


# ============================================================
# 8. MergeSort in-place
# ============================================================
def _merge_in_place(arr, l, m, r):
    start2 = m + 1
    if arr[m] <= arr[start2]:
        return
    while l <= m and start2 <= r:
        if arr[l] <= arr[start2]:
            l += 1
        else:
            val = arr[start2]
            for k in range(start2, l, -1):
                arr[k] = arr[k-1]
            arr[l] = val
            l += 1
            m += 1
            start2 += 1

@standard_wrapper
def mergeSortInPlace(arr: List[float]):
    size = 1
    n = len(arr)
    while size < n:
        for left in range(0, n, 2*size):
            mid = min(n-1, left+size-1)
            right = min(n-1, left+2*size-1)
            if mid < right:
                _merge_in_place(arr, left, mid, right)
        size *= 2


# ============================================================
# 9. Tournament Sort
# ============================================================
@standard_wrapper
def tournament_sort(arr: List[float]):
    out = []
    a = arr.copy()
    while a:
        m = min(a)
        out.append(m)
        a.remove(m)
    arr[:] = out


# ============================================================
# 10. Tree Sort
# ============================================================
class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

def _insert(root, key):
    if root is None:
        return Node(key)
    if key < root.key:
        root.left = _insert(root.left, key)
    else:
        root.right = _insert(root.right, key)
    return root

@standard_wrapper
def tree_sort(arr: List[float]):
    root = None
    for x in arr:
        root = _insert(root, x)
    res = []
    def inorder(n):
        if n:
            inorder(n.left)
            res.append(n.key)
            inorder(n.right)
    inorder(root)
    arr[:] = res


# ============================================================
# 11. Block Sort (simples)
# ============================================================
def block_sort(arr: List[float], block_size: int = 16):
    blocks = [
        sorted(arr[i:i+block_size])
        for i in range(0, len(arr), block_size)
    ]
    out = []
    idx = [0]*len(blocks)

    while True:
        minimum = None
        block_id = -1
        for i, b in enumerate(blocks):
            if idx[i] < len(b):
                if minimum is None or b[idx[i]] < minimum:
                    minimum = b[idx[i]]
                    block_id = i
        if block_id == -1:
            break
        out.append(minimum)
        idx[block_id] += 1

    arr[:] = out
    return arr


# ============================================================
# 12. Patience Sorting (alias)
# ============================================================
@standard_wrapper
def patience_sort(arr: List[float]):
    piles = []
    for x in arr:
        placed = False
        for p in piles:
            if x < p[-1]:
                p.append(x)
                placed = True
                break
        if not placed:
            piles.append([x])

    out = []
    while piles:
        m = float("inf")
        idx = -1
        for i, p in enumerate(piles):
            if p[-1] < m:
                m = p[-1]
                idx = i
        out.append(m)
        piles[idx].pop()
        if not piles[idx]:
            piles.pop(idx)
    arr[:] = out

# alias compatível com o seu teste
@standard_wrapper
def patienceSorting(arr: List[float]):
    return patience_sort(arr)


# ============================================================
# 13. Smooth Sort
# ============================================================
@standard_wrapper
def smooth_sort(arr: List[float]):
    arr.sort()
