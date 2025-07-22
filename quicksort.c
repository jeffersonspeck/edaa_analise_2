/*
[PT-BR]
------------------------------------------------------------
Implementação do algoritmo QuickSort em C.

Este código ordena um vetor de inteiros utilizando o algoritmo QuickSort,
baseado no paradigma de divisão e conquista. Em cada chamada recursiva,
um elemento é escolhido como pivô (neste caso, o último elemento do vetor),
e o vetor é particionado em duas partes:
- à esquerda, os elementos menores que o pivô,
- à direita, os elementos maiores.

O processo é aplicado recursivamente sobre as subpartições.

Funções principais:
- `partition`: organiza os elementos em torno do pivô.
- `quicksort`: realiza a ordenação recursiva.

Métricas coletadas:
- `comparacoes`: número de comparações entre elementos.

Complexidade assintótica:
- Melhor caso: O(n log n)
- Pior caso: O(n²) (ex: vetor já ordenado ou decrescente)
- Caso médio: O(n log n)
------------------------------------------------------------

[EN]
------------------------------------------------------------
Implementation of the QuickSort algorithm in C.

This code sorts an integer array using the QuickSort algorithm,
based on the divide-and-conquer paradigm. At each recursive call,
an element is selected as the pivot (here, the last element),
and the array is partitioned into two parts:
- left: elements less than the pivot,
- right: elements greater than the pivot.

The process is recursively applied to each subarray.

Main functions:
- `partition`: rearranges elements around the pivot.
- `quicksort`: performs recursive sorting.

Collected metrics:
- `comparacoes`: number of element comparisons performed.

Asymptotic complexity:
- Best case: O(n log n)
- Worst case: O(n²) (e.g., already sorted or reversed array)
- Average case: O(n log n)
------------------------------------------------------------
*/
#include "quicksort.h"
#include "utils.h"

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparacoes++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
