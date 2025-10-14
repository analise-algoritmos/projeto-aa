CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -O2

all: linear_test quadratic_test logarithmic_test

# Testes dos algoritmos lineares (Counting, Radix e Bucket)
linear_test: src/linear.c tests/test_linear.c
	$(CC) $(CFLAGS) -o $@ $^

# Testes dos algoritmos quadraticos (BubbleSort, InsertionSort, CombSort, SelectionSort, ShellSort, GnomeSort, ShakerSort, OddEvenSort, PancakeSort)
quadratic_test: src/quadratic.c tests/test_quadratic.c
	$(CC) $(CFLAGS) -o $@ $^

# Testes dos algoritmos logartimicos (Heapsort, Introsort, Merge sort, Timsort, Quicksort)
logarithmic_test: src/logarithmic.c tests/test_logarithmic.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f linear_test quadratic_test logarithmic_test

