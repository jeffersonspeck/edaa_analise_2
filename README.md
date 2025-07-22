# Análise Experimental de Algoritmos de Ordenação `O(n log₂ n)`

Este projeto realiza a **análise empírica comparativa** dos algoritmos de ordenação **QuickSort**, **MergeSort** e **HeapSort**, aplicados a diferentes conjuntos de dados de entrada. São coletadas métricas como:

- Tempo de execução
- Número de comparações realizadas
- Uso estimado de memória dinâmica

Os resultados são exibidos no terminal e também exportados para o arquivo `results.csv`.

---

## Estrutura do Projeto

```
sorting_project/
├── README.md             # Este documento aqui
├── heapsort.c            # Implementação do algoritmo HeapSort
├── heapsort.h
├── main.c                # Programa principal para teste automatizado
├── mergesort.c           # Implementação do algoritmo MergeSort
├── mergesort.h
├── quicksort.c           # Implementação do algoritmo QuickSort
├── quicksort.h
├── utils.c               # Funções auxiliares: leitura, tempo, métricas
├── utils.h
├── backup_data/          # Dados originais e completos para restaurar os testes
├── data/                 # Conjuntos de dados de entrada
│   ├── a100.txt          # 100 elementos aleatórios
│   ├── d100.txt          # 100 elementos decrescentes
│   ├── o100.txt          # 100 elementos ordenados crescentes
│   ├── po100.txt         # 100 elementos parcialmente ordenados
│   └── ...
└── output/               # Resultados da execução (gerado automaticamente)
    ├── log.txt           # Resultado do console
    └── results.csv       # Resultados da execução (gerado automaticamente)
````

---

## Compilação

No terminal (Linux, macOS ou WSL):

```bash
gcc -o sort_analysis main.c quicksort.c mergesort.c heapsort.c utils.c -Wall
````

---

## Execução

Após compilar, execute o programa com:

```bash
./sort_analysis
```

Se quiser salvar o log do console, basta utilizar o `tee` (necessário instalar):

```bash
./sort_analysis | tee output/log.txt
```

O programa irá:

1. Varrer automaticamente a pasta `data/` em busca de arquivos `.txt`;
2. Inferir o tipo de dado (aleatório, ordenado, decrescente, etc.) com base no prefixo do nome do arquivo (`a`, `o`, `d`, `po`);
3. Extrair o número de elementos do nome do arquivo (ex: `a500.txt` = 500 elementos);
4. Executar **QuickSort**, **MergeSort** e **HeapSort** sobre cada vetor;
5. Medir o tempo, contagem de comparações e uso de memória;
6. Registrar os dados no terminal e no arquivo `output/results.csv`.

---

## Formato do `results.csv`

Exemplo de conteúdo:

```
Filename,DataType,Size,Algorithm,TimeSeconds,Comparisons,MemoryBytes
a100.txt,Random,100,QuickSort,0.000007,142,0
a100.txt,Random,100,MergeSort,0.000017,157,800
a100.txt,Random,100,HeapSort,0.000011,198,0
...
```

Este arquivo pode ser aberto em Excel, Google Sheets, LibreOffice ou analisado por scripts em Python, R, etc.

---

## Formato dos Arquivos de Dados

Os arquivos na pasta `data/` devem conter **apenas números inteiros, um por linha**, sem cabeçalho.

Exemplo (`a100.txt`):

```
34
7
23
32
5
62
12
90
18
45
...
```

O programa determina automaticamente o tamanho do vetor com base no nome do arquivo (`a100.txt` → 100 números aleatórios lidos).

---

## Algoritmos de Ordenação

### QuickSort

O QuickSort é um algoritmo recursivo que utiliza a técnica de **divisão e conquista**. Em cada passo, escolhe um **pivô** (neste projeto, o último elemento) e particiona o vetor em duas partes: à esquerda, elementos menores; à direita, elementos maiores.

* **Melhor caso**: O(n log n) → pivô sempre divide o vetor ao meio.
* **Pior caso**: O(n²) → vetor já ordenado ou decrescente (pivô mal escolhido).
* **Médio**: O(n log n)
* **Memória**: In-place (uso mínimo)

---

### MergeSort

O MergeSort é um algoritmo **estável**, baseado em divisão e conquista. Divide o vetor recursivamente em metades e depois realiza a **intercalação ordenada**.

* **Melhor caso**: O(n log n)
* **Pior caso**: O(n log n)
* **Médio**: O(n log n)
* **Memória**: O(n) extra (vetores auxiliares)

---

### HeapSort

O HeapSort transforma o vetor em uma **árvore heap (máx-heap)** e, em seguida, extrai o maior elemento repetidamente, reorganizando o heap a cada passo.

* **Melhor caso**: O(n log n)
* **Pior caso**: O(n log n)
* **Médio**: O(n log n)
* **Memória**: In-place

---

## Observações Técnicas

* Todos os algoritmos foram instrumentados para contar o número de **comparações** realizadas.
* A variável `memoria` registra o uso estimado com `malloc` e `realloc`.
* O projeto é modular, permitindo fácil extensão com outros algoritmos.
* O QuickSort pode ser melhorado com pivô aleatório ou mediana de três (não implementado aqui).
* Vetores com até 10⁵ elementos são viáveis de testar sem otimizações adicionais.

---

## Autores

* Edinéia dos Santos Brizola Brum
* Jefferson Rodrigo Speck
* Rafael Ferreira Lima

---

## Referências

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2002). Algoritmos: Teoria e Prática (2ª ed., tradução da 2ª ed. americana). Rio de Janeiro: Campus.

---
