# Algoritmos de Ordenação (Python)

Biblioteca Python contendo algoritmos de ordenação implementados para fins acadêmicos na disciplina de **Análise de Algoritmos**.  
Atualmente, contém o algoritmo **Bubble Sort**, mas o objetivo é expandir para incluir pelo outros algoritmos.

---

## 📁 Estrutura do projeto
lib-python/
│
├── src/ # Código da biblioteca
│ ├── init.py
│ └── bubble_sort.py
│
├── tests/ # Testes unitários
│ └── test_bubble_sort.py
│
├── pyproject.toml # Configuração para instalação
├── README.md
└── requirements.txt

---

## ⚙️ Como buildar
Antes de tudo, instale as dependências necessárias:
```bash
pip install build pytest
```

Em seguida, gere os arquivos de distribuição:
```bash
python -m build
```

Os artefatos serão criados na pasta dist/:
```cmd
dist/
├── lib_python_aa-0.1.0.tar.gz
└── lib_python_aa-0.1.0-py3-none-any.whl
```

## 🧪 Como executar os testes
```bash
python -m pytest -v
```

## 💻 Como usar localmente
```python
from src import bubble_sort

lista = [5, 2, 9, 1]
ordenada = bubble_sort(lista)
print(ordenada)  # [1, 2, 5, 9]
```

Se quiser instalar localmente após o build:
```bash
pip install dist/lib_python_aa-0.1.0-py3-none-any.whl
```