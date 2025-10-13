CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -O2

all: linear_test quadratic_test

# Testes dos algoritmos lineares (Counting, Radix e Bucket)
linear_test: src/linear.cpp tests/test_linear.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Testes dos algoritmos quadraticos (BubbleSort, InsertionSort, CombSort, SelectionSort, ShellSort, GnomeSort, ShakerSort, OddEvenSort, PancakeSort)
quadratic_test:
	$(CXX) $(CXXFLAGS) -o quadratic_test src/quadratic.cpp tests/test_quadratic.cpp

clean:
	rm -f linear_test quadratic_test