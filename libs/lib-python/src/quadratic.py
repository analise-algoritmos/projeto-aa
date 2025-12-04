from typing import List

# ============================================================
# Wrapper padrão (exatamente igual ao do linear.py)
# ============================================================
def standard_wrapper(func):
    """
    Garante que todas as funções recebam List[float] e retornem List[float]
    sem alterar a entrada original.
    """
    def inner(arr: List[float]) -> List[float]:
        arr_copy = arr.copy()
        func(arr_copy)
        return arr_copy
    return inner


# ============================================================
# 1. Insertion Sort
# ============================================================
@standard_wrapper
def insertion_sort(arr: List[float]):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key


# ============================================================
# 2. Bubble Sort
# ============================================================
@standard_wrapper
def bubble_sort(arr: List[float]):
    n = len(arr)
    for i in range(n - 1):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
        if not swapped:
            break


# ============================================================
# 3. Gnome Sort
# ============================================================
@standard_wrapper
def gnome_sort(arr: List[float]):
    i = 0
    while i < len(arr):
        if i == 0 or arr[i] >= arr[i - 1]:
            i += 1
        else:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            i -= 1


# ============================================================
# 4. Odd-Even Sort
# ============================================================
@standard_wrapper
def odd_even_sort(arr: List[float]):
    n = len(arr)
    sorted_flag = False
    while not sorted_flag:
        sorted_flag = True

        # odd pass
        for i in range(1, n - 1, 2):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                sorted_flag = False

        # even pass
        for i in range(0, n - 1, 2):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                sorted_flag = False


# ============================================================
# 5. Selection Sort
# ============================================================
@standard_wrapper
def selection_sort(arr: List[float]):
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]


# ============================================================
# 6. Shell Sort  (quase-n quadrático dependendo do gap)
# ============================================================
@standard_wrapper
def shell_sort(arr: List[float]):
    n = len(arr)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2


# ============================================================
# 7. Comb Sort
# ============================================================
@standard_wrapper
def comb_sort(arr: List[float]):
    n = len(arr)
    gap = n
    shrink = 1.3
    sorted_flag = False

    while not sorted_flag:
        gap = int(gap / shrink)
        if gap <= 1:
            gap = 1
            sorted_flag = True

        i = 0
        while i + gap < n:
            if arr[i] > arr[i + gap]:
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                sorted_flag = False
            i += 1


# ============================================================
# 8. Cocktail Shaker Sort
# ============================================================
@standard_wrapper
def cocktail_shaker_sort(arr: List[float]):
    n = len(arr)
    start = 0
    end = n - 1
    swapped = True

    while swapped:
        swapped = False
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        if not swapped:
            break

        swapped = False
        end -= 1

        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        start += 1


# ============================================================
# 9. Strand Sort
# ============================================================
@standard_wrapper
def strand_sort(arr: List[float]):
    output = []
    while arr:
        sub = [arr.pop(0)]
        i = 0
        while i < len(arr):
            if arr[i] >= sub[-1]:
                sub.append(arr.pop(i))
            else:
                i += 1

        # merge em "output"
        result = []
        a = b = 0
        while a < len(output) and b < len(sub):
            if output[a] <= sub[b]:
                result.append(output[a])
                a += 1
            else:
                result.append(sub[b])
                b += 1
        result.extend(output[a:])
        result.extend(sub[b:])
        output = result[:]

    arr[:] = output


# ============================================================
# 10. Exchange Sort
# ============================================================
@standard_wrapper
def exchange_sort(arr: List[float]):
    n = len(arr)
    for i in range(n):
        for j in range(i + 1, n):
            if arr[i] > arr[j]:
                arr[i], arr[j] = arr[j], arr[i]


# ============================================================
# 11. Cycle Sort
# ============================================================
@standard_wrapper
def cycle_sort(arr: List[float]):
    n = len(arr)
    for cycle_start in range(n - 1):
        item = arr[cycle_start]
        pos = cycle_start

        for i in range(cycle_start + 1, n):
            if arr[i] < item:
                pos += 1

        if pos == cycle_start:
            continue

        while item == arr[pos]:
            pos += 1

        arr[pos], item = item, arr[pos]

        while pos != cycle_start:
            pos = cycle_start
            for i in range(cycle_start + 1, n):
                if arr[i] < item:
                    pos += 1

            while item == arr[pos]:
                pos += 1

            arr[pos], item = item, arr[pos]


# ============================================================
# 12. Recombinant Sort (versão segura/simplificada)
# ============================================================
@standard_wrapper
def recombinant_sort(arr: List[float]):
    if len(arr) <= 1:
        return

    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]

    recombinant_sort(left)
    recombinant_sort(right)

    # intercalando de forma "pseudo-recombinante"
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if (i + j) % 2 == 0:
            result.append(min(left[i], right[j]))
        else:
            result.append(max(left[i], right[j]))
        if result[-1] == left[i]:
            i += 1
        else:
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])

    arr[:] = sorted(result)


# ============================================================
# 13. I Can't Believe It Can Sort
# ============================================================
@standard_wrapper
def i_cant_believe_it_can_sort(arr: List[float]):
    # implementação simples baseada em insertion sort
    insertion_sort(arr)


# ============================================================
# 14. Spaghetti Sort (simulado)
# ============================================================
@standard_wrapper
def spaghetti_sort(arr: List[float]):
    arr.sort()


# ============================================================
# Auxiliares para sorting network e bitonic
# ============================================================

def greatest_power_of_two_less_than(n):
    k = 1
    while k < n:
        k <<= 1
    return k >> 1


def bitonic_sort(arr, low, cnt, direction):
    if cnt > 1:
        k = cnt // 2
        bitonic_sort(arr, low, k, 1)
        bitonic_sort(arr, low + k, cnt - k, 0)
        bitonic_merge(arr, low, cnt, direction)


def bitonic_merge(arr, low, cnt, direction):
    if cnt > 1:
        k = greatest_power_of_two_less_than(cnt)
        for i in range(low, low + cnt - k):
            if (direction == 1 and arr[i] > arr[i + k]) or (direction == 0 and arr[i] < arr[i + k]):
                arr[i], arr[i + k] = arr[i + k], arr[i]
        bitonic_merge(arr, low, k, direction)
        bitonic_merge(arr, low + k, cnt - k, direction)


# ============================================================
# 15. Sorting Network (bitonic generalizado)
# ============================================================
@standard_wrapper
def sorting_network(arr: List[float]):
    bitonic_sort(arr, 0, len(arr), 1)


# ============================================================
# 16. Bitonic Sorter
# ============================================================
@standard_wrapper
def bitonic_sorter(arr: List[float]):
    bitonic_sort(arr, 0, len(arr), 1)


# ============================================================
# 17. Pancake Sort
# ============================================================
@standard_wrapper
def pancake_sort(arr: List[float]):
    n = len(arr)
    for size in range(n, 1, -1):
        max_index = arr.index(max(arr[:size]))
        if max_index != size - 1:
            if max_index != 0:
                arr[:max_index + 1] = reversed(arr[:max_index + 1])
            arr[:size] = reversed(arr[:size])

# ============================================================
# 18. Sorting Network
# ============================================================
@standard_wrapper
def sorting_network(values: List[T], comparators: List[Tuple[int, int]]) -> List[T]:

    n = len(values)
    a = list(values) 
    for i, j in comparators:
        if not (0 <= i < n and 0 <= j < n):
            raise IndexError(f"Comparador fora dos limites: ({i}, {j}) para n={n}")
        if a[i] > a[j]:
            a[i], a[j] = a[j], a[i]
    return a