# Análise Experimental de Algoritmos de Ordenação `O(n log₂ n)`

Este projeto realiza a **análise empírica comparativa** dos algoritmos de ordenação **QuickSort**, **MergeSort** e **HeapSort**, aplicados a diferentes conjuntos de dados de entrada. São coletadas métricas como:

- Tempo de execução
- Número de comparações realizadas
- Uso estimado de memória dinâmica

Os resultados são exibidos no terminal e também exportados para o arquivo `results.csv`.

Os arquivos-fonte deste projeto foram feitos em `C` e contêm comentários extensos em português e inglês com o objetivo de documentar detalhadamente o funcionamento de cada algoritmo, suas métricas e complexidade. Esses blocos de comentários podem ser livremente removidos ou reduzidos caso deseje um código mais limpo ou enxuto para entrega ou execução prática.

Os resultados da análise foram compilados em um arquivo PDF a partir do fonte em `LaTeX` e os fontes estão em disponíveis em `report/`
---

## Índice

- [Estrutura do Projeto](#estrutura-do-projeto)
- [Compilação](#compilação)
- [Execução](#execução)
- [Formato do `results.csv`](#formato-do-resultscsv)
- [Formato dos Arquivos de Dados](#formato-dos-arquivos-de-dados)
- [Algoritmos de Ordenação](#algoritmos-de-ordenação)
  - [QuickSort](#quicksort)
  - [MergeSort](#mergesort)
  - [HeapSort](#heapsort)
- [Observações Técnicas](#observações-técnicas)
- [Manipulação e Análise dos Dados](#manipulação-e-análise-dos-dados)
  - [Agrupador de Resultados de Testes](#agrupador-de-resultados-de-testes-de-algoritmos-de-ordenação)
  - [Plot dos Resultados](#plot-dos-resultados)
    - [Estrutura Esperada](#estrutura-esperada)
    - [O que o script faz](#o-que-o-script-faz)
    - [Gráficos Gerados](#gráficos-gerados)
    - [Como Executar](#como-executar)
    - [Gráficos](#gráficos)
    - [Requisitos](#requisitos)
    - [Observações](#observações)
- [Autores](#autores)
- [Referências](#referências)


## Estrutura do Projeto

```
sorting_project/
├── README.md                     # Este documento aqui
├── heapsort.c                    # Implementação do algoritmo HeapSort
├── heapsort.h
├── main.c                        # Programa principal para teste automatizado
├── mergesort.c                   # Implementação do algoritmo MergeSort
├── mergesort.h
├── quicksort.c                   # Implementação do algoritmo QuickSort
├── quicksort.h
├── utils.c                       # Funções auxiliares: leitura, tempo, métricas
├── utils.h
├── analyses/                     # Scripts Python para análise estatística e visualização
|   ├── group_files.py            # Script para agrupar arquivos CSV por rodada de teste
|   └── group_and_graph.py        # Script para gerar métricas e gráficos automaticamente
├── backup_data/                  # Dados originais e completos para restaurar os testes
├── data/                         # Conjuntos de dados de entrada
│   ├── a100.txt                  # 100 elementos aleatórios
│   ├── d100.txt                  # 100 elementos decrescentes
│   ├── o100.txt                  # 100 elementos ordenados crescentes
│   ├── po100.txt                 # 100 elementos parcialmente ordenados
│   └── ...                       # Outros arquivos gerados para testes
├── graphs/                       # Gráficos gerados com matplotlib/seaborn
│   ├── quicksort_tempo_por_tipo_dado.png
│   ├── mergesort_tempo_com_std_por_tipo_dado.png
│   ├── tempo_comparativo_por_algoritmo_random.png
│   └── ...                       # Outros gráficos para cada algoritmo e tipo de dados
├── output/                       # Resultados da execução (gerado automaticamente)
│   ├── 1_results.csv             # Resultados da execução teste 1
│   ├── 2_results.csv             # Resultados da execução teste 2
│   ├── ...                       # Outras rodadas de teste
│   ├── combined_by_test.csv      # Resultados combinados de todos os testes
│   ├── metrics_filtered_with_std.csv  # Métricas com média e desvio padrão
│   └── log.txt                   # Resultado do console
└── report/                       # Resultado compilado em um artigo e fonte em Latex
    ├── report.pdf                # Relatório técnico
    ├── report.zip                # Fontes do relatório em Latex 
```

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

O QuickSort é um algoritmo recursivo que utiliza a técnica de **divisão e conquista**. Em cada passo, escolhe um **pivô** (neste projeto, o meio) e particiona o vetor em duas partes: à esquerda, elementos menores; à direita, elementos maiores.

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

# Manipulação e Analise dos Dados

Aqui está um `README.md` explicando claramente a finalidade, funcionamento e instruções de uso do código fornecido:

---

##  Agrupador de Resultados de Testes de Algoritmos de Ordenação

Este script Python tem como objetivo **agrupar e consolidar os resultados de múltiplos testes de desempenho de algoritmos de ordenação** (como QuickSort, MergeSort e HeapSort), que foram previamente salvos em arquivos `.csv` separados. Ele é útil para organizar os dados experimentais e facilitar análises estatísticas posteriores em Python, Excel, R ou outras ferramentas.

---

### Funcionalidade

O script realiza as seguintes etapas:

1. **Procura por arquivos CSV** com nomes no formato `N_results.csv` (onde `N` é o número do teste) dentro da pasta `../output`.
2. **Ordena os arquivos** com base no número do teste (por exemplo: `1_results.csv`, `2_results.csv`, ...).
3. **Lê cada arquivo** e insere uma nova coluna chamada `Test`, indicando de qual rodada de teste aquele conjunto de resultados pertence.
4. **Agrupa todos os arquivos lidos** em um único DataFrame pandas.
5. **Salva o resultado consolidado** no arquivo `combined_by_test.csv` dentro da pasta `../output/`.

---

### Estrutura Esperada

```
project_root/
├── analyses/
│   └── group_files.py       ← Este script
├── output/
│   ├── 1_results.csv
│   ├── 2_results.csv
│   ├── ...
│   └── combined_by_test.csv ← Gerado automaticamente
```

---

### Exemplo de Entrada

Cada arquivo como `1_results.csv` deve conter colunas como:

```
Filename,DataType,Size,Algorithm,TimeSeconds,Comparisons,MemoryBytes
a100.txt,Random,100,QuickSort,0.000007,53,0
...
```

---

### Exemplo de Saída (`combined_by_test.csv`)

```csv
Test,Filename,DataType,Size,Algorithm,TimeSeconds,Comparisons,MemoryBytes
1,a100.txt,Random,100,QuickSort,0.000007,53,0
1,a100.txt,Random,100,MergeSort,0.000008,66,800
1,a100.txt,Random,100,HeapSort,0.000009,61,0
2,a100.txt,Random,100,QuickSort,0.000006,48,0
...
```

---

### Como Executar

A partir da pasta onde está o script:

```bash
python group_files.py
```

Certifique-se de que a pasta `../output/` contenha os arquivos `N_results.csv`.

---

### Requisitos

* Python 3.x
* Bibliotecas:

  * `pandas` (instale com `pip install pandas`)

---

###  Observações

* O script não utiliza bibliotecas externas além do `pandas`.
* A nomenclatura dos arquivos deve seguir exatamente o padrão `N_results.csv`.
* O número `N` é usado para gerar a coluna `Test` no CSV final.

---

## Plot dos resultados

### Análise Experimental de Algoritmos de Ordenação - Geração de Gráficos

Este script realiza a análise estatística e visualização gráfica dos resultados de experimentos com algoritmos de ordenação (`QuickSort`, `MergeSort` e `HeapSort`) aplicados a diferentes tipos de conjuntos de dados.

### Estrutura Esperada

O arquivo de entrada `combined_by_test.csv` deve estar na pasta `../output/` e conter os resultados brutos de **7 execuções por teste**, incluindo:

- Nome do arquivo (`Filename`)
- Algoritmo (`Algorithm`)
- Tipo de dados (`DataType`)
- Tamanho do vetor (`Size`)
- Tempo de execução (`TimeSeconds`)
- Número de comparações (`Comparisons`)
- Uso de memória (`MemoryBytes`)

### O que o script faz

1. **Remove o melhor e o pior tempo de execução por grupo** (`Filename`, `Algorithm`);
2. **Calcula média e desvio padrão** de tempo, comparações e memória para os 5 testes restantes;
3. **Salva os dados agregados** em um novo arquivo:  
   `../output/metrics_filtered_with_std.csv`;
4. **Gera múltiplos gráficos**, salvos na pasta `graphs/`:

#### Gráficos Gerados

1. **Para cada algoritmo**:
   - Tempo médio por tipo de dados (`tempo_por_tipo_dado`)
   - Tempo médio com desvio padrão (`tempo_com_std_por_tipo_dado`)

2. **Para cada tipo de dados**:
   - Comparação entre algoritmos com barras de erro (`tempo_comparativo_por_algoritmo_<tipo>.png`)

---

### Como executar

1. Garanta que o arquivo `combined_by_test.csv` esteja presente em `../output/`.
2. Execute o script Python:

```bash
python nome_do_script.py
````

3. Verifique a pasta `graphs/` para os arquivos PNG com os gráficos.

---

### Gráficos

* `quicksort_tempo_por_tipo_dado.png`
* `mergesort_tempo_com_std_por_tipo_dado.png`
* `tempo_comparativo_por_algoritmo_random.png`

---

### Requisitos

* Python 3.10+
* Pacotes:

```bash
pip install pandas matplotlib seaborn
```

---

### Observações

* As análises removem os outliers (melhor e pior tempo).
* Os gráficos ajudam a visualizar como cada algoritmo se comporta diante de diferentes cenários de entrada.
* A mesma lógica pode ser estendida para gráficos de **comparações** e **uso de memória**.

---


## Autores

* Edinéia dos Santos Brizola Brum
* Jefferson Rodrigo Speck
* Rafael Ferreira Lima

---

## Referências

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2002). Algoritmos: Teoria e Prática (2ª ed., tradução da 2ª ed. americana). Rio de Janeiro: Campus.

---
