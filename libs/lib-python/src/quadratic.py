def bubble_sort(values):
    n = len(values)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if values[j] > values[j + 1]:
                values[j], values[j + 1] = values[j + 1], values[j]
                swapped = True
        if not swapped:
            break


def insertion_sort(values):
    for i in range(1, len(values)):
        key = values[i]
        j = i - 1
        while j >= 0 and values[j] > key:
            values[j + 1] = values[j]
            j -= 1
        values[j + 1] = key


def comb_sort(values):
    n = len(values)
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
            if values[i] > values[i + gap]:
                values[i], values[i + gap] = values[i + gap], values[i]
                sorted_flag = False
            i += 1


def selection_sort(values):
    n = len(values)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if values[j] < values[min_index]:
                min_index = j
        values[i], values[min_index] = values[min_index], values[i]


def shell_sort(values):
    n = len(values)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = values[i]
            j = i
            while j >= gap and values[j - gap] > temp:
                values[j] = values[j - gap]
                j -= gap
            values[j] = temp
        gap //= 2


def gnome_sort(values):
    n = len(values)
    i = 0
    while i < n:
        if i == 0 or values[i] >= values[i - 1]:
            i += 1
        else:
            values[i], values[i - 1] = values[i - 1], values[i]
            i -= 1


def shaker_sort(values):
    start = 0
    end = len(values) - 1
    swapped = True
    while swapped:
        swapped = False
        for i in range(start, end):
            if values[i] > values[i + 1]:
                values[i], values[i + 1] = values[i + 1], values[i]
                swapped = True
        if not swapped:
            break
        swapped = False
        end -= 1
        for i in range(end - 1, start - 1, -1):
            if values[i] > values[i + 1]:
                values[i], values[i + 1] = values[i + 1], values[i]
                swapped = True
        start += 1


def odd_even_sort(values):
    n = len(values)
    sorted_flag = False
    while not sorted_flag:
        sorted_flag = True
        for i in range(1, n - 1, 2):
            if values[i] > values[i + 1]:
                values[i], values[i + 1] = values[i + 1], values[i]
                sorted_flag = False
        for i in range(0, n - 1, 2):
            if values[i] > values[i + 1]:
                values[i], values[i + 1] = values[i + 1], values[i]
                sorted_flag = False


def flip(values, i):
    values[:i + 1] = values[:i + 1][::-1]


def find_max_index(values, n):
    mi = 0
    for i in range(1, n):
        if values[i] > values[mi]:
            mi = i
    return mi


def pancake_sort(values):
    n = len(values)
    for curr_size in range(n, 1, -1):
        mi = find_max_index(values, curr_size)
        if mi != curr_size - 1:
            flip(values, mi)
            flip(values, curr_size - 1)


def bitonic_sort(arr):
    n = len(arr)
    for k in range(2, n+1):
        j = k // 2
        while j > 0:
            for i in range(0, n):
                l = i ^ j
                if l > i:
                    if ( ((i&k)==0) and (arr[i] > arr[l]) or ( ( (i&k)!=0) and (arr[i] < arr[l])) ):
                        temp = arr[i]
                        arr[i] = arr[l]
                        arr[l] = temp
            j //= 2


def cocktail_shaker_sort(arr):
    n = len(arr)
    start = 0
    end = n - 1
    swapped = True
    while swapped:
        swapped = False
        # Passagem da esquerda para a direita
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        end -= 1
        # Passagem da direita para a esquerda
        for i in range(end, start, -1):
            if arr[i] < arr[i - 1]:
                arr[i], arr[i - 1] = arr[i - 1], arr[i]
                swapped = True
        start += 1


def merge(a, b):
    result = []
    i = j = 0
    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            result.append(a[i])
            i += 1
        else:
            result.append(b[j])
            j += 1
    result.extend(a[i:])
    result.extend(b[j:])
    return result


def strand_sort(arr):
    result = []
    arr = arr[:]  # Evita modificar lista original
    while arr:
        strand = [arr.pop(0)]
        i = 0
        while i < len(arr):
            if arr[i] >= strand[-1]:
                strand.append(arr.pop(i))
            else:
                i += 1
        result = merge(result, strand)
    return result


def exchange_sort(values):
    n = len(values)
    for i in range(n - 1):
        for j in range(i + 1, n):
            if values[i] > values[j]:
                values[i], values[j] = values[j], values[i]


def cycle_sort(arr):
    n = len(arr)
    for cycle_start in range(n - 1):
        item = arr[cycle_start]
        pos = cycle_start
        # Encontra a posicao correta do item
        for i in range(cycle_start + 1, n):
            if arr[i] < item:
                pos += 1
        # Pula se o item ja esta na posicao correta
        if pos == cycle_start:
            continue
        while item == arr[pos]:
            pos += 1
        arr[pos], item = item, arr[pos]
        # Continua com novos ciclos ate retornar ao inicio
        while pos != cycle_start:
            pos = cycle_start
            for i in range(cycle_start + 1, n):
                if arr[i] < item:
                    pos += 1
            while item == arr[pos]:
                pos += 1
            arr[pos], item = item, arr[pos]


def recombinant_sort(arr: List[float]) -> None:
    # Count array 10x10
    S = [[0 for _ in range(10)] for _ in range(10)]
    H_min = [10] * 10
    H_max = [-1] * 10

    # ---------- Hashing Cycle ----------
    for x in arr:
        scaled = int(round(x * 10.0))  # 4.5 -> 45

        if scaled < 0 or scaled > 99:
            # fora do intervalo suportado
            continue

        i = scaled // 10
        j = scaled % 10

        S[i][j] += 1
        if j < H_min[i]:
            H_min[i] = j
        if j > H_max[i]:
            H_max[i] = j

    # ---------- Extraction Cycle ----------
    idx = 0
    for i in range(10):
        if H_max[i] == -1:
            continue

        for j in range(H_min[i], H_max[i] + 1):
            while S[i][j] > 0:
                arr[idx] = i + j / 10.0
                idx += 1
                S[i][j] -= 1


def icbics(arr):
    B = sorted(arr)
    n = len(arr)
    while arr != B:
        for i in range(n):
            # Busca binaria na ordenacao canonica
            left, right = 0, n - 1
            while left <= right:
                mid = (left + right) // 2
                if B[mid] == arr[i]:
                    if i != mid:
                        arr[i], arr[mid] = arr[mid], arr[i]
                    break
                elif B[mid] < arr[i]:
                    left = mid + 1
                else:
                    right = mid - 1
    return arr


def spaghetti_sort(arr):
    n = len(arr)
    used = [False] * n
    result = []
    for _ in range(n):
        max_val = float('-inf')
        idx = -1
        for i in range(n):
            if not used[i] and arr[i] > max_val:
                max_val = arr[i]
                idx = i
        result.insert(0, max_val)  # Insere no inicio para ficar em ordem crescente
        used[idx] = True
    return result


def sorting_network(values: List[T], comparators: List[Tuple[int, int]]) -> List[T]:

    n = len(values)
    a = list(values) 
    for i, j in comparators:
        if not (0 <= i < n and 0 <= j < n):
            raise IndexError(f"Comparador fora dos limites: ({i}, {j}) para n={n}")
        if a[i] > a[j]:
            a[i], a[j] = a[j], a[i]
    return a