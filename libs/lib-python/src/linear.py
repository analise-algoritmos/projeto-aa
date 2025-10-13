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
