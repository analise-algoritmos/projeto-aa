CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -O2

all: bubble_sort_test linear_test

bubble_sort_test: src/bubble_sort.c tests/test_bubble_sort.c
	$(CC) $(CFLAGS) -o $@ $^

# Teste do linear (Counting, Radix e Bucket)
linear_test: src/linear.c tests/test_linear.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f bubble_sort_test linear_test