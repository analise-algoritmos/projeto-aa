# Algoritmos de Ordenação

Biblioteca Python contendo algoritmos de ordenação implementados para fins acadêmicos na disciplina de Análise de Algoritmos.  
Atualmente, contém o algoritmo Bubble Sort, mas o objetivo é expandir para pelo menos 50 algoritmos diferentes.

## Estrutura do projeto
lib-python/
│
├── sorting_algorithms/ # Código da biblioteca
│ ├── init.py
│ └── bubble_sort.py
│
├── tests/ # Testes unitários
│ └── test_bubble_sort.py
│
├── setup.py # Configuração para instalação
├── README.md
└── requirements.txt

## Como usar

```python
from sorting_algorithms import bubble_sort

lista = [5, 2, 9, 1]
ordenada = bubble_sort(lista)
print(ordenada)  # [1, 2, 5, 9]
```

## Como testar
```bash
python -m unittest discover tests
```