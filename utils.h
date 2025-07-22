#ifndef UTILS_H
#define UTILS_H

extern long comparacoes;
extern long memoria;

void resetar_metricas();
int* carregar_dados(const char* filename, int* tamanho);
void salvar_saida(const char* filename, int arr[], int n);
double tempo_execucao(void (*sort_func)(int[], int), int arr[], int n);

#endif
