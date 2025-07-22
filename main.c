#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "utils.h"

void wrapper_quick(int arr[], int n) { quicksort(arr, 0, n - 1); }
void wrapper_merge(int arr[], int n) { mergesort(arr, 0, n - 1); }

int main() {
    const char* arquivos[] = {
        "dados/aleatorio.txt",
        "dados/ordenado.txt",
        "dados/parcial.txt",
        "dados/decrescente.txt"
    };

    const char* nomes[] = { "Aleatório", "Ordenado", "Parcialmente Ordenado", "Decrescente" };

    FILE* csv = fopen("resultados.csv", "w");
    fprintf(csv, "TipoEntrada,Algoritmo,TempoSegundos,Comparacoes,MemoriaBytes\n");

    for (int i = 0; i < 4; i++) {
        int n;
        int* dados1 = carregar_dados(arquivos[i], &n);
        int* dados2 = malloc(n * sizeof(int));
        int* dados3 = malloc(n * sizeof(int));
        memcpy(dados2, dados1, n * sizeof(int));
        memcpy(dados3, dados1, n * sizeof(int));

        resetar_metricas();
        double tq = tempo_execucao(wrapper_quick, dados1, n);
        fprintf(csv, "%s,QuickSort,%.6f,%ld,%ld\n", nomes[i], tq, comparacoes, memoria);

        resetar_metricas();
        double tm = tempo_execucao(wrapper_merge, dados2, n);
        fprintf(csv, "%s,MergeSort,%.6f,%ld,%ld\n", nomes[i], tm, comparacoes, memoria);

        resetar_metricas();
        double th = tempo_execucao(heapsort, dados3, n);
        fprintf(csv, "%s,HeapSort,%.6f,%ld,%ld\n", nomes[i], th, comparacoes, memoria);

        printf("\nConjunto: %s (n = %d)\n", nomes[i], n);
        printf("QuickSort:  %.6f s\n", tq);
        printf("MergeSort:  %.6f s\n", tm);
        printf("HeapSort:   %.6f s\n", th);

        free(dados1); free(dados2); free(dados3);
    }

    fclose(csv);
    return 0;
}
