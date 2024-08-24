#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 4096

typedef struct {
    unsigned long long bits[MAX_VERTICES / 64];
} BitSet;

void setBit(BitSet *set, int index) {
    int i = index / 64;
    int j = index % 64;
    set->bits[i] |= (1ULL << j);
}

int getBit(BitSet *set, int index) {
    int i = index / 64;
    int j = index % 64;
    return ((set->bits[i] >> j) & 1ULL);
}

int verificaClique(int vertices, int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], BitSet *subset) {
    for (int i = 0; i < vertices; i++) {
        if (!getBit(subset, i)) continue;
        for (int j = i + 1; j < vertices; j++) {
            if (!getBit(subset, j)) continue;
            if (!adjacencyMatrix[i][j]) return 0; // Aresta ausente na clique
        }
    }
    return 1; // Todos os pares de vértices são adjacentes na clique
}

double medirTempoExecucao(int vertices, int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], BitSet *subset, int repeticoes) {
    clock_t inicio, fim;
    double tempoTotal = 0.0;
    for (int i = 0; i < repeticoes; i++) {
        inicio = clock();
        verificaClique(vertices, adjacencyMatrix, subset);
        fim = clock();
        double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoTotal += tempoExecucao;
    }
    return tempoTotal / repeticoes;
}

void gerarGrafoAleatorio(int vertices, double densidade, int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]) {
    int maxArestas = (vertices * (vertices - 1)) / 2;
    int arestasDesejadas = densidade * maxArestas;
    srand(time(NULL));

    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    int contadorArestas = 0;
    while (contadorArestas < arestasDesejadas) {
        int i = rand() % vertices;
        int j = rand() % vertices;
        if (i != j && !adjacencyMatrix[i][j]) {
            adjacencyMatrix[i][j] = 1;
            adjacencyMatrix[j][i] = 1;
            contadorArestas++;
        }
    }
}

double *estimarTempoExecucao(int from, int to, int by, int nsamples, double dens, int nrep, double r) {
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    double *temposMedios = malloc(((to - from) / by + 1) * sizeof(double));
    int index = 0;

    for (int vertices = from; vertices <= to; vertices += by) {
        double tempoTotal = 0.0;

        for (int sample = 0; sample < nsamples; sample++) {
            BitSet subset;
            for (int i = 0; i < MAX_VERTICES / 64; i++) {
                subset.bits[i] = 0ULL;
            }

            gerarGrafoAleatorio(vertices, dens, adjacencyMatrix);

            int numVerticesSubset = vertices * r;
            for (int i = 0; i < numVerticesSubset; i++) {
                int randomIndex = rand() % vertices;
                setBit(&subset, randomIndex);
            }

            double tempoMedio = medirTempoExecucao(vertices, adjacencyMatrix, &subset, nrep);
            tempoTotal += tempoMedio;
        }

        temposMedios[index] = tempoTotal / nsamples;
        index++;
    }

    return temposMedios;
}

int main() {
    int from = 100;
    int to = 500;
    int by = 100;
    int nsamples = 10;
    double dens = 0.5;
    int nrep = 5;
    double r = 0.5;

    double *temposMedios = estimarTempoExecucao(from, to, by, nsamples, dens, nrep, r);

    printf("Tempos Médios:\n");
    int numPontos = (to - from) / by + 1;
    for (int i = 0; i < numPontos; i++) {
        printf("Vertices: %d, Tempo Médio: %lf\n", from + i * by, temposMedios[i]);
    }

    free(temposMedios);

    return 0;
}
