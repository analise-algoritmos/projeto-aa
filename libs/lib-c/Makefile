CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -O2

all: bubble_sort_test

bubble_sort_test: src/bubble_sort.c tests/test_bubble_sort.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f bubble_sort_test