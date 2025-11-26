def counting_sort(arr, k):
    count = [0] * (k + 1)
    output = [0] * len(arr)

    for num in arr:
        count[num] += 1
    for i in range(1, len(count)):
        count[i] += count[i - 1]
    for num in reversed(arr):
        output[count[num] - 1] = num
        count[num] -= 1

    return output


# LSD Radix Sort (usa counting sort internamente)
def radix_sort(arr):
    m = max(arr)
    exp = 1
    while m // exp > 0:
        count = [0] * 10
        output = [0] * len(arr)

        for num in arr:
            index = (num // exp) % 10
            count[index] += 1
        for i in range(1, 10):
            count[i] += count[i - 1]
        for num in reversed(arr):
            index = (num // exp) % 10
            output[count[index] - 1] = num
            count[index] -= 1

        arr = output
        exp *= 10
    return arr


def bucket_sort(arr):
    n = len(arr)
    buckets = [[] for _ in range(n)]

    # Distribuição dos elementos
    for num in arr:
        index = int(n * num)
        if index == n:  # evita índice fora do intervalo se num == 1.0
            index -= 1
        buckets[index].append(num)

    # Ordena cada bucket usando insertion sort inline
    for b in range(n):
        bucket = buckets[b]
        for i in range(1, len(bucket)):
            key = bucket[i]
            j = i - 1
            while j >= 0 and bucket[j] > key:
                bucket[j + 1] = bucket[j]
                j -= 1
            bucket[j + 1] = key
        buckets[b] = bucket

    # Concatena todos os buckets
    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(bucket)

    return sorted_arr

def spreadsort(arr):
    if len(arr) <= 1:
        return arr
    min_val, max_val = min(arr), max(arr)
    if min_val == max_val:
        return arr
    pivot = (min_val + max_val) // 2
    left = [x for x in arr if x <= pivot]
    right = [x for x in arr if x > pivot]
    return spreadsort(left) + spreadsort(right)


def burstsort(arr):
    buckets = [[] for _ in range(256)]
    for s in arr:
        buckets[ord(s[0])].append(s)
    sorted_arr = []
    for b in buckets:
        sorted_arr.extend(b)
    return sorted_arr


def flashsort(arr):
    n = len(arr)
    m = int(0.45 * n)
    L = [0] * m
    min_val, max_val = min(arr), max(arr)
    if min_val == max_val:
        return arr
    c1 = (m - 1) / (max_val - min_val)
    for x in arr:
        k = int(c1 * (x - min_val))
        L[k] += 1
    for i in range(1, m):
        L[i] += L[i - 1]
    count, j = 0, 0
    while count < n:
        while j >= len(L):
            L.pop()
        evicted = arr[j]
        while True:
            k = int(c1 * (evicted - min_val))
            arr[L[k] - 1], evicted = evicted, arr[L[k] - 1]
            L[k] -= 1
            count += 1
            if j == L[k]:
                break
        j += 1
    return arr


def postman_sort(arr, base=10):
    max_val = max(arr)
    exp = 1
    n = len(arr)
    output = [0] * n
    while max_val // exp > 0:
        count = [0] * base
        for num in arr:
            count[(num // exp) % base] += 1
        for i in range(1, base):
            count[i] += count[i - 1]
        for i in reversed(range(n)):
            idx = (arr[i] // exp) % base
            output[count[idx] - 1] = arr[i]
            count[idx] -= 1
        arr = output[:]
        exp *= base
    return arr


def bead_sort(arr):
    if any(x < 0 for x in arr):
        raise ValueError("Apenas inteiros não-negativos")
    n = len(arr)
    max_val = max(arr)
    beads = [[0] * max_val for _ in range(n)]
    for i, num in enumerate(arr):
        for j in range(num):
            beads[i][j] = 1
    for j in range(max_val):
        sum_col = sum(beads[i][j] for i in range(n))
        for i in range(n):
            beads[i][j] = 1 if i >= n - sum_col else 0
    for i in range(n):
        arr[i] = sum(beads[i])
    return arr


def pigeonhole_sort(arr):
    if not arr:
        return []
    mi, ma = min(arr), max(arr)
    size = ma - mi + 1
    holes = [[] for _ in range(size)]
    for x in arr:
        holes[x - mi].append(x)
    i = 0
    for hole in holes:
        for x in hole:
            arr[i] = x
            i += 1
    return arr


def bucket_sort_whole_keys(arr, b=10):
    if not arr:
        return []
    mi, ma = min(arr), max(arr)
    if mi == ma:
        return arr[:]
    size = (ma - mi + 1) / b
    buckets = [[] for _ in range(b)]
    for x in arr:
        idx = int((x - mi) / size)
        if idx == b:  # Caso extremo (maior valor)
            idx -= 1
        buckets[idx].append(x)
    # Ordena cada bucket (Insertion Sort)
    for bucket in buckets:
        for i in range(1, len(bucket)):
            key = bucket[i]
            j = i - 1
            while j >= 0 and bucket[j] > key:
                bucket[j + 1] = bucket[j]
                j -= 1
            bucket[j + 1] = key
    # Concatena todos os buckets
    out = []
    for bucket in buckets:
        out.extend(bucket)
    return out
