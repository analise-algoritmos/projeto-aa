def bubble_sort(values):
    """
    Ordena uma lista de valores usando o algoritmo Bubble Sort.
    
    Parâmetros:
    values (list): lista de números a serem ordenados
    
    Retorna:
    list: a lista ordenada
    """
    n = len(values)
    for i in range(n):
        swapped = False  
        for j in range(0, n-i-1):
            if values[j] > values[j+1]:
                values[j], values[j+1] = values[j+1], values[j]
                swapped = True
        if not swapped:
            break
    return values
