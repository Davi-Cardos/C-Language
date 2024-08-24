#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 4096

typedef unsigned long long int bitmap;

int verificaClique(int n, bitmap *matriz, bitmap subconjunto) {
    int i, j;
    for (i = 0; i < n; i++) {
        if ((subconjunto & (1ull << i)) == 0) {
            continue;
        }
        for (j = i + 1; j < n; j++) {
            if ((subconjunto & (1ull << j)) == 0) {
                continue;
            }
            if ((matriz[i] & (1ull << j)) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

double medirTempoExecucao(int nrep, int n, bitmap *matriz, bitmap subconjunto) {
    int i;
    double tempoTotal = 0.0;
    clock_t inicio, fim;
    for (i = 0; i < nrep; i++) {
        inicio = clock();
        verificaClique(n, matriz, subconjunto);
        fim = clock();
        tempoTotal += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    return tempoTotal / nrep;
}

void gerarGrafoAleatorio(int n, double densidade, bitmap *matriz) {
    int i, j;
    memset(matriz, 0, sizeof(bitmap) * n);
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if ((double)rand() / RAND_MAX <= densidade) {
                matriz[i] |= (1ull << j);
                matriz[j] |= (1ull << i);
            }
        }
    }
}

double *estimarTempoExecucao(int from, int to, int by, int nsamples,
                             double densidade, int nrep, double r) {
    int i, j;
    double *tempos = malloc(sizeof(double) * ((to - from) / by + 1));
    bitmap *matriz = malloc(sizeof(bitmap) * MAX_VERTICES);
    for (i = from; i <= to; i += by) {
        double tempoTotal = 0.0;
        for (j = 0; j < nsamples; j++) {
            gerarGrafoAleatorio(i, densidade, matriz);
            bitmap subconjunto =
                ((1ull << (int)(i * r)) - 1ull) & ((1ull << i) - 1ull);
            tempoTotal += medirTempoExecucao(nrep, i, matriz, subconjunto);
        }
        tempos[(i - from) / by] = tempoTotal / nsamples;
    }
    free(matriz);
    return tempos;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSAMPLES 10
#define NREP 10000
#define R 0.1

void plot_graph() {
    int vertices[] = {1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840, 4096};
    double densities[] = {0.1, 0.5, 0.6, 0.9, 0.99};
    for (int i = 0; i < sizeof(densities) / sizeof(densities[0]); i++) {
        double times[sizeof(vertices) / sizeof(vertices[0])];
        for (int j = 0; j < sizeof(vertices) / sizeof(vertices[0]); j++) {
            int n = vertices[j];
            double density = densities[i];
            char command[100];
            printf("./graph %d %f %d", n, density, NSAMPLES);
            double total_time = 0;
            for (int k = 0; k < NREP; k++) {
                clock_t start = clock();
                system(command);
                clock_t end = clock();
                total_time += (double)(end - start) / CLOCKS_PER_SEC;
            }
            times[j] = total_time / NREP;
        }
        printf("Densidade: %f\n", densities[i]);
        printf("Vertices\tTempo\n");
        for (int j = 0; j < sizeof(vertices) / sizeof(vertices[0]); j++) {
            printf("%d\t%f\n", vertices[j], times[j]);
        }
    }
}

int main() {
    plot_graph();
    return 0;
}