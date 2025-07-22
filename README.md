Claro! Aqui está um `README.md` completo para o seu projeto de ordenação em C, com instruções claras para compilação, execução, estrutura dos arquivos e análise dos resultados.

---

```markdown
# Projeto: Análise Experimental de Algoritmos de Ordenação \(O(n \log n)\)

Este projeto realiza a comparação de desempenho dos algoritmos **QuickSort**, **MergeSort** e **HeapSort** aplicados a diferentes conjuntos de dados de entrada. São coletadas métricas de tempo de execução, número de comparações e uso estimado de memória dinâmica. Os resultados são salvos em um arquivo `resultados.csv`.

---

## 📁 Estrutura do Projeto

```

sorting\_project/
├── main.c                # Programa principal
├── quicksort.c/.h        # Algoritmo QuickSort
├── mergesort.c/.h        # Algoritmo MergeSort
├── heapsort.c/.h         # Algoritmo HeapSort
├── utils.c/.h            # Utilitários: carregamento de dados, tempo, métricas
├── resultados.csv        # (Gerado na execução) Resultados em formato CSV
└── dados/
├── aleatorio.txt
├── ordenado.txt
├── parcial.txt
└── decrescente.txt

````

---

## 🚀 Compilação

No terminal (Linux/Mac/WSL):

```bash
gcc -o ordenacao main.c quicksort.c mergesort.c heapsort.c utils.c -Wall
````

---

## ▶️ Execução

Execute o programa com:

```bash
./ordenacao
```

O programa irá:

* Carregar os arquivos de entrada da pasta `dados/`
* Executar os 3 algoritmos sobre cada conjunto
* Medir o tempo, número de comparações e uso de memória
* Exibir os resultados no terminal
* Registrar os resultados em `resultados.csv`

---

## 📊 Formato do `resultados.csv`

Após a execução, o arquivo conterá linhas como:

```
TipoEntrada,Algoritmo,TempoSegundos,Comparacoes,MemoriaBytes
Aleatório,QuickSort,0.000523,17,0
Aleatório,MergeSort,0.000673,23,80
...
```

Você pode abrir este arquivo em planilhas (Excel, LibreOffice, Google Sheets) ou usar Python/R para gerar gráficos.

---

## 📥 Formato dos Arquivos de Dados

Cada arquivo da pasta `dados/` deve começar com um número inteiro que indica a quantidade de elementos, seguido pelos elementos (um por linha). Exemplo (`aleatorio.txt`):

```
10
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
```

---

## 🧪 Conjuntos de Entrada Usados

* `aleatorio.txt`: elementos aleatórios
* `ordenado.txt`: elementos já em ordem crescente
* `parcial.txt`: mistura de ordenados e fora de ordem
* `decrescente.txt`: elementos em ordem decrescente

---

## 📌 Observações

* O código é modular e facilmente extensível para outros algoritmos ou métricas.
* Os algoritmos foram instrumentados para contar comparações e alocações de memória (quando aplicável).
* `MergeSort` é o único que usa `malloc` para dividir vetores; os demais operam in-place.

---

## 👨‍💻 Autores

* Edinéia dos Santos Brizola Brum
* Jefferson Rodrigo Speck
* Rafael Ferreira Lima

---

```

---

Se desejar, posso incluir esse `README.md` já no projeto `.zip` atualizado com métricas e CSV. Quer que eu gere essa nova versão empacotada?
```

