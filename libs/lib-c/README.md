# Algoritmos de Ordenação (C)

Biblioteca em linguagem C contendo algoritmos de ordenação implementados para fins acadêmicos na disciplina de **Análise de Algoritmos**.  
Atualmente, contém o algoritmo **Bubble Sort**, mas o objetivo é expandir para incluir outros algoritmos.

---

## 📁 Estrutura do projeto
lib-c/
│
├── include/ # Cabeçalhos (.h)
│ └── bubble_sort.h
│
├── src/ # Código-fonte (.c)
│ └── bubble_sort.c
│
├── tests/ # Testes e exemplos
│ └── test_bubble_sort.c
│
├── Makefile # Configuração de build
└── README.md

---

## ⚙️ Como buildar
Antes de tudo, certifique-se de ter o compilador **GCC** instalado.  
Em seguida, execute o comando abaixo para compilar o projeto:

```bash
make
```
O processo irá gerar o executável bubble_sort_test na pasta atual.

## 🧪 Como executar os testes
Após o build, execute o teste principal:

```bash
./bubble_sort_test
```
A saída será apresentada no terminal.

## 🧹 Limpar build
Para remover o executável gerado e recompilar do zero:
```bash
make clean
```