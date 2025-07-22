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
