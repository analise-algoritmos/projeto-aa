CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -O2

# Alvo padrão: compila todos os testes
all: bubble_sort_test linear_test

# Teste do bubble sort
bubble_sort_test: src/bubble_sort.cpp tests/test_bubble_sort.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Teste do linear (counting, radix, bucket)
linear_test: src/linear.cpp tests/test_linear.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpeza dos binários
clean:
	rm -f bubble_sort_test linear_test
