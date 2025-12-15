import math
from typing import List, TypeVar, Callable

T = TypeVar("T")

def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[-1]
    left  = [x for x in arr[:-1] if x <= pivot]
    right = [x for x in arr[:-1] if x > pivot]
    return quicksort(left) + [pivot] + quicksort(right)

def fluxsort(arr):
    if len(arr) <= 16:
        return sorted(arr)
    # Seleciona pivo como a mediana de tres valores
    pivot = sorted([arr[0], arr[len(arr)//2], arr[-1]])[1]
    left  = [x for x in arr if x < pivot]
    mid   = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return fluxsort(left) + mid + fluxsort(right)

def crumsort(arr):
    if len(arr) <= 16:
        return sorted(arr)
    # Escolhe a mediana de tres como pivo
    pivot = sorted([arr[0], arr[len(arr)//2], arr[-1]])[1]
    left  = [x for x in arr if x < pivot]
    mid   = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return crumsort(left) + mid + crumsort(right)


def library_sort(arr):
    import math
    n = len(arr)
    eps = 1
    size = math.ceil((1 + eps) * n)
    B = [None] * size
    mid = size // 2
    B[mid] = arr[0]
    for x in arr[1:]:
        # Coleta indices dos elementos ocupados (nao-Nenhum)
        idxs = [i for i, v in enumerate(B) if v is not None]
        # Busca posicao de insercao via busca binaria
        left, right = 0, len(idxs)
        while left < right:
            m = (left + right) // 2
            if B[idxs[m]] < x:
                left = m + 1
            else:
                right = m
        insert_pos = idxs[left] if left < len(idxs) else size - 1
        # Avanca ate encontrar gap
        k = insert_pos
        while k < size and B[k] is not None:
            k += 1
        # Desloca elementos
        while k > insert_pos:
            B[k] = B[k - 1]
            k -= 1
        B[insert_pos] = x
        # (Ignora realocacao de gaps por simplicidade)
    # Retorna os elementos ordenados, ignorando gaps
    return [v for v in B if v is not None]

def msd_radix_sort(arr, pos=None):
    if not arr:
        return arr
    if pos is None:
        max_len = len(str(max(arr)))
        pos = max_len - 1
    if len(arr) <= 1 or pos < 0:
        return arr
    buckets = [[] for _ in range(10)]
    for n in arr:
        s = str(n).zfill(pos + 1)
        digit = int(s[-(pos + 1)])
        buckets[digit].append(n)
    out = []
    for b in buckets:
        if b:
            out.extend(msd_radix_sort(b, pos - 1))
    return out

def get_digit(num, pos, max_digits):
    return (num // 10 ** (max_digits - pos - 1)) % 10

def msd_radix_sort_in_place(arr, ini=0, fim=None, pos=0, max_digits=None):
    if fim is None:
        fim = len(arr)
    if not arr or fim - ini <= 1:
        return
    if max_digits is None:
        max_digits = len(str(max(arr)))
    if pos >= max_digits:
        return
    count = [0] * 10
    for i in range(ini, fim):
        d = get_digit(arr[i], pos, max_digits)
        count[d] += 1
    start = [ini]
    for c in count[:-1]:
        start.append(start[-1] + c)
    cur = start.copy()
    i = ini
    while i < fim:
        d = get_digit(arr[i], pos, max_digits)
        j = cur[d]
        if i != j:
            arr[i], arr[j] = arr[j], arr[i]
        else:
            i += 1
        cur[d] += (i == j)
    for b in range(10):
        s = start[b]
        e = start[b] + count[b]
        if count[b] > 1:
            msd_radix_sort_in_place(arr, s, e, pos + 1, max_digits)

def merge_insertion_sort(arr):
    n = len(arr)
    if n <= 1:
        return arr.copy()
    # Forma pares de elementos
    pairs = [
        (arr[i], arr[i + 1]) if i + 1 < n else (arr[i],)
        for i in range(0, n, 2)
    ]
    # Ordena cada par
    sorted_pairs = [tuple(sorted(p)) for p in pairs]
    left = [p[0] for p in sorted_pairs]
    right = [p[1] for p in sorted_pairs if len(p) == 2]
    # Ordena recursivamente o lado esquerdo
    base = merge_insertion_sort(left)
    # Insere cada elemento do lado direito na lista base
    from bisect import insort
    for x in right:
        insort(base, x)
    return base

    
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L, R = arr[:mid], arr[mid:]
        merge_sort(L)
        merge_sort(R)
        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

def heapify(arr, n, i):
    largest = i
    l, r = 2*i + 1, 2*i + 2
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heapsort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)


def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i + 1

def insertion_sort(arr, l=0, r=None):
    if r is None:
        r = len(arr) - 1
    for i in range(l + 1, r + 1):
        key = arr[i]
        j = i - 1
        while j >= l and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def introsort_rec(arr, start, end, depth_limit):
    size = end - start + 1
    if size < 16:
        insertion_sort(arr, start, end)
        return
    if depth_limit == 0:
        # aplica heapsort parcial
        subarr = arr[start:end+1]
        heapsort(subarr)
        arr[start:end+1] = subarr
        return
    pivot = partition(arr, start, end)
    introsort_rec(arr, start, pivot - 1, depth_limit - 1)
    introsort_rec(arr, pivot + 1, end, depth_limit - 1)

def introsort(arr):
    if len(arr) <= 1:
        return arr
    depth_limit = 2 * int(math.log2(len(arr)))
    introsort_rec(arr, 0, len(arr) - 1, depth_limit)
    return arr

RUN = 32
def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def timsort(arr):
    n = len(arr)
    for i in range(0, n, RUN):
        insertion_sort(arr, i, min(i + RUN - 1, n - 1))

    size = RUN
    while size < n:
        for left in range(0, n, 2 * size):
            mid = left + size
            right = min(left + 2 * size, n)
            if mid < right:
                merged = merge(arr[left:mid], arr[mid:right])
                arr[left:left + len(merged)] = merged
        size *= 2
    return arr

def slowsort(A, i, j):
		if i >= j:
			return
		m = (i+j)/2
		slowsort(A, i, m)   
		slowsort(A, m+1, j)
		if A[m] > A[j]:
			A[m],A[j] = A[j],A[m]
		slowsort(A, i, j-1)
          
# Linear sort
def _merge(left: List[T], right: List[T]) -> List[T]:
    i = j = 0
    out: List[T] = []
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            out.append(left[i]); i += 1
        else:
            out.append(right[j]); j += 1
    out.extend(left[i:])
    out.extend(right[j:])
    return out

def mergesort(arr: List[T]) -> List[T]:
    n = len(arr)
    if n <= 1:
        return arr[:]
    mid = n // 2
    left = mergesort(arr[:mid])
    right = mergesort(arr[mid:])
    return _merge(left, right)

def linear_sort(lst: List[T], scale: float = 0.001) -> List[T]:
    start = time.perf_counter()
    sorted_list = mergesort(lst)
    elapsed = time.perf_counter() - start
    target = scale * len(lst) - elapsed
    if target > 0:
        time.sleep(target)
    return sorted_list

def cubesort(arr):
    sorted_list = []
    for x in arr:
        i = 0
        while i < len(sorted_list) and sorted_list[i] < x:
            i += 1
        sorted_list.insert(i, x)
    return sorted_list

def merge(array, from1, to1, from2, to2, buffer):
    while from1 <= to1 and from2 <= to2:
        if array[from1] <= array[from2]:
            array[from1], array[buffer] = array[buffer], array[from1]
            from1 += 1
        else:
            array[from2], array[buffer] = array[buffer], array[from2]
            from2 += 1
        buffer += 1

    while from1 <= to1:
        array[from1], array[buffer] = array[buffer], array[from1]
        from1 += 1
        buffer += 1

    while from2 <= to2:
        array[from2], array[buffer] = array[buffer], array[from2]
        from2 += 1
        buffer += 1

def AdvancedInPlaceMergeSort(array, start, end, buffer):
    if start >= end:
        array[start], array[buffer] = array[buffer], array[start]
    else:
        mid = (start + end) // 2
        mergeSort(array, start, mid)
        mergeSort(array, mid + 1, end)
        merge(array, start, mid, mid + 1, end, buffer)

def mergeSortInPlace(array, start, end):
    if start < end:
        mid = (start + end + 1) // 2 - 1
        buffer = end - (mid - start)
        AdvancedInPlaceMergeSort(array, start, mid, buffer)
        L2, R2 = buffer, end
        L1, R1 = start, L2 - 1

        while R1 - L1 > 1:
            mid = (L1 + R1) // 2
            length = R1 - mid - 1
            AdvancedInPlaceMergeSort(array, mid + 1, R1, mid + 1)
            merge(array, L1, L1 + length - 1, L2, R2, R1 - length + 1)
            R1 -= length
            L2 = R1 + 1

        for i in range(R1, L1 - 1, -1):
            j = i + 1
            while j <= end and array[j - 1] > array[j]:
                array[j - 1], array[j] = array[j], array[j - 1]
                j += 1

# Tournament Sort
INF = float('inf')

def tournament_sort(arr):
    n = len(arr)
    tmp = [0] * (2 * n)

    def winner(pos1, pos2):
        u = pos1 if pos1 >= n else tmp[pos1]
        v = pos2 if pos2 >= n else tmp[pos2]
        return u if tmp[u] <= tmp[v] else v

    def create_tree():
        for i in range(n):
            tmp[n + i] = arr[i]

        for i in range(2 * n - 1, 1, -2):
            parent = i // 2
            sibling = i - 1
            tmp[parent] = winner(i, sibling)

        value = tmp[tmp[1]]
        tmp[tmp[1]] = INF
        return value

    def recreate():
        i = tmp[1]
        while i > 1:
            parent = i // 2
            if i % 2 == 0 and i < 2 * n - 1:
                sibling = i + 1
            else:
                sibling = i - 1

            tmp[parent] = winner(i, sibling)
            i = parent

        value = tmp[tmp[1]]
        tmp[tmp[1]] = INF
        return value

    result = []
    value = create_tree()
    for _ in range(n):
        result.append(value)
        value = recreate()

    return result

# Tree Sort
class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


def insertRec(root, key):
    if root is None:
        return Node(key)

    if key < root.key:
        root.left = insertRec(root.left, key)
    elif key > root.key:
        root.right = insertRec(root.right, key)

    return root


def tree_sort(arr):
    # monta árvore
    root = None
    for x in arr:
        root = insertRec(root, x)

    # coleta elementos ordenados
    result = []

    def inorder(root):
        if root:
            inorder(root.left)
            result.append(root.key)
            inorder(root.right)

    inorder(root)
    return result

# Block Sort
def block_sort(arr, block_size):
    blocks = []
    for i in range(0, len(arr), block_size):
        block = arr[i:i + block_size]
        blocks.append(sorted(block))

    result = []
    while blocks:
        min_idx = 0
        for i in range(1, len(blocks)):
            if blocks[i][0] < blocks[min_idx][0]:
                min_idx = i
        result.append(blocks[min_idx].pop(0))
        if len(blocks[min_idx]) == 0:
            blocks.pop(min_idx)
    return result

# Patience Sorting 

def merge_piles(v):
    ans = []

    while True:
        minu = float("inf")
        index = -1
        for i in range(len(v)):
            if minu > v[i][-1]:
                minu = v[i][-1]
                index = i
        ans.append(minu)
        v[index].pop()
        if not v[index]:
            v.pop(index)
        if not v:
            break

    return ans

def patienceSorting(arr):
    piles = []

    for i in range(len(arr)):
        if not piles:
            temp = []
            temp.append(arr[i])
            piles.append(temp)
        else:
            flag = True
            for j in range(len(piles)):
                if arr[i] < piles[j][-1]:
                    piles[j].append(arr[i])
                    flag = False
                    break
            if flag:
                temp = []
                temp.append(arr[i])
                piles.append(temp)

    ans = []

    ans = merge_piles(piles)
    return ans

# Smooth Sort
def smooth_sort(arr):
    n = len(arr)

    def leonardo(k):
        if k < 2:
            return 1
        return leonardo(k - 1) + leonardo(k - 2) + 1
    def heapify(start, end):
        i = start
        j = 0
        k = 0

        while k < end - start + 1:
            if k & 0xAAAAAAAA:
                j = j + i
                i = i >> 1
            else:
                i = i + j
                j = j >> 1

            k = k + 1

        while i > 0:
            j = j >> 1
            k = i + j
            while k < end:
                if arr[k] > arr[k - i]:
                    break
                arr[k], arr[k - i] = arr[k - i], arr[k]
                k = k + i

            i = j

    p = n - 1
    q = p
    r = 0
    while p > 0:
        if (r & 0x03) == 0:
            heapify(r, q)

        if leonardo(r) == p:
            r = r + 1
        else:
            r = r - 1
            q = q - leonardo(r)
            heapify(r, q)
            q = r - 1
            r = r + 1

        arr[0], arr[p] = arr[p], arr[0]
        p = p - 1

    for i in range(n - 1):
        j = i + 1
        while j > 0 and arr[j] < arr[j - 1]:
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
            j = j - 1

    return arr