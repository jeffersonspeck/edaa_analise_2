/*
[PT-BR]
------------------------------------------------------------
Funções utilitárias para suporte à análise de algoritmos de ordenação.

Este módulo contém funções auxiliares utilizadas pelo programa principal:
- Medição de tempo de execução dos algoritmos (`tempo_execucao`)
- Leitura de dados a partir de arquivos (`carregar_dados`)
- Escrita opcional de vetores ordenados em arquivos (`salvar_saida`)
- Controle e reinicialização de métricas globais:
  - `comparacoes`: número de comparações entre elementos
  - `memoria`: quantidade estimada de memória alocada (bytes)

Observações:
- A função `carregar_dados` está adaptada para arquivos que iniciam com
  um inteiro representando o tamanho do vetor seguido pelos elementos.
- A contagem de memória considera apenas a alocação via `malloc`.

Uso típico:
- As métricas são resetadas antes de cada execução de algoritmo.
- A função `tempo_execucao` executa o algoritmo e retorna a duração em segundos.

------------------------------------------------------------

[EN]
------------------------------------------------------------
Utility functions for supporting the analysis of sorting algorithms.

This module provides helper functions used by the main program:
- Measuring execution time of sorting algorithms (`tempo_execucao`)
- Reading input data from files (`carregar_dados`)
- Optional saving of sorted arrays to files (`salvar_saida`)
- Control and reset of global metrics:
  - `comparacoes`: number of element comparisons
  - `memoria`: estimated memory usage (in bytes)

Notes:
- The `carregar_dados` function expects files to begin with an integer
  indicating the array size, followed by the elements.
- Memory count considers only memory allocated via `malloc`.

Typical usage:
- Metrics are reset before each algorithm execution.
- `tempo_execucao` runs the sorting function and returns elapsed time in seconds.

------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

long comparacoes = 0;
long memoria = 0;

void resetar_metricas() {
    comparacoes = 0;
    memoria = 0;
}

int* carregar_dados(const char* filename, int* tamanho) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    fscanf(file, "%d", tamanho);
    int* arr = malloc((*tamanho) * sizeof(int));
    memoria += (*tamanho) * sizeof(int);

    for (int i = 0; i < *tamanho; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
    return arr;
}

void salvar_saida(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

double tempo_execucao(void (*sort_func)(int[], int), int arr[], int n) {
    clock_t inicio = clock();
    sort_func(arr, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}
