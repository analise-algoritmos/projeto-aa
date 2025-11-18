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