import random

def stoogesort(arr, l, h):
  if l >= h:
      return

  if arr[l]>arr[h]:
      t = arr[l]
      arr[l] = arr[h]
      arr[h] = t


  if h-l + 1 > 2:
      t = (int)((h-l + 1)/3)

      stoogesort(arr, l, (h-t))
      stoogesort(arr, l + t, (h))
      stoogesort(arr, l, (h-t))

def bogo_sort(a):
    n = len(a)
    while (is_sorted(a)== False):
        shuffle(a)

def is_sorted(a):
    n = len(a)
    for i in range(0, n-1):
        if (a[i] > a[i+1] ):
            return False
    return True

def shuffle(a):
    n = len(a)
    for i in range (0,n):
        r = random.randint(0,n-1)
        a[i], a[r] = a[r], a[i] 