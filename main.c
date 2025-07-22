/*
[PT-BR]
------------------------------------------------------------
Programa principal para análise experimental de algoritmos de ordenação.

Este programa automatiza a execução e medição de desempenho dos algoritmos:
- QuickSort
- MergeSort
- HeapSort

Fluxo geral:
1. Percorre automaticamente a pasta `data/` procurando arquivos de entrada.
2. Identifica o tipo de dados (aleatório, ordenado, etc.) pelo prefixo do nome do arquivo.
3. Extrai a quantidade de elementos a partir do nome do arquivo (ex: a500.txt → 500).
4. Carrega os dados do arquivo e executa cada algoritmo de ordenação.
5. Mede o tempo de execução, número de comparações e uso de memória dinâmica.
6. Grava os resultados no terminal e no arquivo `output/results.csv`.

Formato do CSV:
- Filename, DataType, Size, Algorithm, TimeSeconds, Comparisons, MemoryBytes

Dependências:
- Funções auxiliares em `utils.c` para tempo e métricas
- Algoritmos implementados separadamente em seus respectivos arquivos

Observação:
- O diretório `output/` deve existir antes da execução
------------------------------------------------------------

[EN]
------------------------------------------------------------
Main program for experimental analysis of sorting algorithms.

This program automates the execution and performance measurement of:
- QuickSort
- MergeSort
- HeapSort

General flow:
1. Automatically scans the `data/` folder for input files.
2. Identifies data type (random, sorted, etc.) from the filename prefix.
3. Extracts the number of elements from the filename (e.g., a500.txt → 500).
4. Loads input data and executes each sorting algorithm.
5. Measures execution time, number of comparisons, and dynamic memory usage.
6. Logs results to the console and to the `output/results.csv` file.

CSV Format:
- Filename, DataType, Size, Algorithm, TimeSeconds, Comparisons, MemoryBytes

Dependencies:
- Auxiliary functions in `utils.c` for timing and metrics
- Sorting algorithms implemented in separate modules

Note:
- The `output/` directory must exist prior to execution
------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "utils.h"

void wrapper_quick(int arr[], int n) { quicksort(arr, 0, n - 1); }
void wrapper_merge(int arr[], int n) { mergesort(arr, 0, n - 1); }

const char* detect_type(const char* filename) {
    if (strncmp(filename, "po", 2) == 0) return "Partially Ordered";
    if (strncmp(filename, "a", 1) == 0) return "Random";
    if (strncmp(filename, "o", 1) == 0) return "Sorted";
    if (strncmp(filename, "d", 1) == 0) return "Descending";
    return "Unknown";
}

int extract_size(const char* filename) {
    const char* p = filename;
    while (*p && !isdigit(*p)) p++;
    return atoi(p);
}

int* load_fixed_data(const char* filename, int size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    int* data = malloc(size * sizeof(int));
    memoria += size * sizeof(int);

    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &data[i]) != 1) {
            fprintf(stderr, "Error: file %s contains fewer than %d integers.\n", filename, size);
            exit(1);
        }
    }

    fclose(file);
    return data;
}

int main() {
    DIR* dir_ptr;
    struct dirent* entry;
    dir_ptr = opendir("data/");
    if (!dir_ptr) {
        perror("Error opening data/ directory");
        return 1;
    }

    FILE* csv = fopen("output/results.csv", "w");
    if (!csv) {
        perror("Error creating output/results.csv");
        return 1;
    }

    fprintf(csv, "Filename,DataType,Size,Algorithm,TimeSeconds,Comparisons,MemoryBytes\n");

    while ((entry = readdir(dir_ptr)) != NULL) {
        if (entry->d_type == DT_REG) {
            char path[512];
            snprintf(path, sizeof(path), "data/%s", entry->d_name);

            const char* type = detect_type(entry->d_name);
            int size = extract_size(entry->d_name);

            int* data1 = load_fixed_data(path, size);
            int* data2 = malloc(size * sizeof(int));
            int* data3 = malloc(size * sizeof(int));
            memcpy(data2, data1, size * sizeof(int));
            memcpy(data3, data1, size * sizeof(int));

            resetar_metricas();
            double t_quick = tempo_execucao(wrapper_quick, data1, size);
            fprintf(csv, "%s,%s,%d,QuickSort,%.6f,%ld,%ld\n", entry->d_name, type, size, t_quick, comparacoes, memoria);

            resetar_metricas();
            double t_merge = tempo_execucao(wrapper_merge, data2, size);
            fprintf(csv, "%s,%s,%d,MergeSort,%.6f,%ld,%ld\n", entry->d_name, type, size, t_merge, comparacoes, memoria);

            resetar_metricas();
            double t_heap = tempo_execucao(heapsort, data3, size);
            fprintf(csv, "%s,%s,%d,HeapSort,%.6f,%ld,%ld\n", entry->d_name, type, size, t_heap, comparacoes, memoria);

            printf("\nFile: %s (Type: %s, Size = %d)\n", entry->d_name, type, size);
            printf("QuickSort:  %.6f s\n", t_quick);
            printf("MergeSort:  %.6f s\n", t_merge);
            printf("HeapSort:   %.6f s\n", t_heap);

            free(data1); free(data2); free(data3);
        }
    }

    fclose(csv);
    closedir(dir_ptr);
    return 0;
}