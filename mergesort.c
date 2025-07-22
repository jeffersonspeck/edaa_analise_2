/*
[PT-BR]
------------------------------------------------------------
Implementação do algoritmo MergeSort em C.

Este código realiza a ordenação de um vetor de inteiros utilizando o algoritmo MergeSort,
baseado na estratégia de divisão e conquista. O vetor é dividido recursivamente ao meio
e os subvetores são intercalados de forma ordenada na função `merge`.

Durante o processo, são coletadas métricas para análise de desempenho:
- `comparacoes`: contador de comparações entre elementos;
- `memoria`: quantidade de memória alocada dinamicamente com malloc.

A função `mergesort` faz a divisão recursiva e `merge` realiza a junção ordenada.

Complexidade assintótica:
- Melhor, médio e pior caso: O(n log n)
------------------------------------------------------------

[EN]
------------------------------------------------------------
Implementation of the MergeSort algorithm in C.

This code performs sorting of an integer array using the MergeSort algorithm,
which follows the divide-and-conquer paradigm. The array is recursively split in half,
and the sorted subarrays are merged in the `merge` function.

Performance metrics collected during execution:
- `comparacoes`: counter for number of element comparisons;
- `memoria`: amount of dynamically allocated memory via malloc.

The `mergesort` function performs the recursive division,
and `merge` handles the ordered merging of subarrays.

Asymptotic complexity:
- Best, average, and worst case: O(n log n)
------------------------------------------------------------
*/
#include <stdlib.h>
#include "mergesort.h"
#include "utils.h"

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    memoria += n1 * sizeof(int) + n2 * sizeof(int);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        comparacoes++;
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergesort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
