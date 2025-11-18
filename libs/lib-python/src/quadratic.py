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