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