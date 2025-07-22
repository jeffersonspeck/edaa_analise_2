/*
[PT-BR]
------------------------------------------------------------
Implementação do algoritmo HeapSort em C.

Este código ordena um vetor de inteiros utilizando o algoritmo HeapSort,
que constrói uma estrutura de heap máximo (max-heap) a partir do vetor
e, em seguida, extrai repetidamente o maior elemento (raiz do heap) para
colocá-lo na posição final, reduzindo o tamanho do heap a cada iteração.

Durante a execução:
- A função `heapify` garante a propriedade de heap para cada subárvore.
- A função `heapsort` primeiro constrói o heap e depois realiza as trocas.

Métricas coletadas:
- `comparacoes`: número de comparações entre elementos.

Complexidade assintótica:
- Melhor caso: O(n log n)
- Pior caso: O(n log n)
- Caso médio: O(n log n)
------------------------------------------------------------

[EN]
------------------------------------------------------------
Implementation of the HeapSort algorithm in C.

This code sorts an integer array using the HeapSort algorithm,
which builds a max-heap from the array and then repeatedly extracts
the largest element (the heap root), placing it at the end and shrinking
the heap size with each iteration.

During execution:
- The `heapify` function ensures the heap property for each subtree.
- The `heapsort` function builds the heap and performs the sorting swaps.

Collected metrics:
- `comparacoes`: number of element comparisons performed.

Asymptotic complexity:
- Best case: O(n log n)
- Worst case: O(n log n)
- Average case: O(n log n)
------------------------------------------------------------
*/
#include "heapsort.h"
#include "utils.h"

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n) { comparacoes++; if (arr[l] > arr[largest]) largest = l; }
    if (r < n) { comparacoes++; if (arr[r] > arr[largest]) largest = r; }

    if (largest != i) {
        int temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        int temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        heapify(arr, i, 0);
    }
}
