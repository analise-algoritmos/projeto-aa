CXX=g++
CXXFLAGS=-Iinclude -Wall -Wextra -O2

all: bubble_sort_test

bubble_sort_test: src/bubble_sort.cpp tests/test_bubble_sort.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f bubble_sort_test