#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 21

void printMatriz(double A[N][N+1]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j <= N; j++) {
            printf("%.2f\t", A[i][j]);
        }
        printf("\n");
    }
}

void Pivoteamento_Parcial(double A[N][N+1], int k) {
    int i, maxlinha;
    double temp, maxVal;

    maxVal = A[k][k];
    maxlinha = k;

    for (i = k + 1; i < N; i++) {
        if (A[i][k] > maxVal) {
            maxVal = A[i][k];
            maxlinha = i;
        }
    }

    if (maxlinha != k) {
        for (i = k; i <= N; i++) {
            temp = A[k][i];
            A[k][i] = A[maxlinha][i];
            A[maxlinha][i] = temp;
        }
    }
}

void Eliminacao_Gauss_Parcial(double A[N][N+1], double x[N]) {
    int i, j, k;
    double mult, aux;

    // chamando em cada laço a funcao do pivoteamento parcial
    for (k = 0; k < N - 1; k++) {
        Pivoteamento_Parcial(A, k);

        for (i = k + 1; i < N; i++) {
            mult = A[i][k] / A[k][k];
            for (j = k; j <= N; j++) {
                A[i][j] -= mult * A[k][j];
            }
        }
    }

    // Substituindo e resolvendo 
    for (i = N - 1; i >= 0; i--) {
        aux = 0.0;
        for (j = i + 1; j < N; j++) {
            aux += A[i][j] * x[j];
        }
        x[i] = (A[i][N] - aux) / A[i][i];
    }
}

void Pivoteamento_Total(double A[N][N+1], int k, int* p, int* q) {
    int i, j;
    double temp, maxVal;
    maxVal = 0.0;

    for (i = k; i < N; i++) {
        for (j = k; j < N; j++) {
            if (abs(A[i][j]) > maxVal) {
                maxVal = abs(A[i][j]);
                *p = i;
                *q = j;
            }
        }
    }

    if (*p != k) {
        for (j = k; j <= N; j++) {
            temp = A[k][j];
            A[k][j] = A[*p][j];
            A[*p][j] = temp;
        }
    }

    if (*q != k) {
        for (i = 0; i < N; i++) {
            temp = A[i][k];
            A[i][k] = A[i][*q];
            A[i][*q] = temp;
        }
    }
}

void Eliminacao_gauss_Total(double A[N][N+1], double x[N]) {
    int i, j, k, p, q;
    double mult, aux;

    // Forward elimination
    for (k = 0; k < N - 1; k++) {
        Pivoteamento_Total(A, k, &p, &q);

        for (i = k + 1; i < N; i++) {
            mult = A[i][k] / A[k][k];
            for (j = k; j <= N; j++) {
                A[i][j] -= mult * A[k][j];
            }
        }
    }

    // substituindo e resolvendo
    for (i = N - 1; i >= 0; i--) {
        aux = 0.0;
        for (j = i + 1; j < N; j++) {
            aux += A[i][j] * x[j];
        }
        x[i] = (A[i][N] - aux) / A[i][i];
    }
}



int main() {
    double A[N][N+1];
    double b[N+1];
    double x[N];
    int i, j;

    // Inicializar a matriz A e o vetor b
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j) {
                A[i][j] = 0.0;
            } else {
                A[i][j] = abs(i - j);
            }
        }
        b[i] = i + 1;
    }

    //Adicionar a última coluna à matriz A 
    for (i = 0; i < N; i++) {
        A[i][N] = b[i];
    }
    // Imprimir a matriz A antes da eliminação
    printf("Matriz A:\n");
    
    printMatriz(A);
    
    
    // Resolver o sistema usando o método de eliminação de Gauss com pivoteamento parcial
    Eliminacao_Gauss_Parcial(A, x);

    // Imprimir a solução
    printf("\nSolucao (eliminacao de Gauss com pivoteamento parcial):\n");
    for (i = 0; i < N; i++) {
        printf("x[%d] = %.2f\n", i, x[i]);
    }

    // Resolver o sistema usando o método de eliminação de Gauss com pivoteamento total
    Eliminacao_gauss_Total(A, x);

    // Imprimir a solução
    printf("\nSolucao (eliminacao de Gauss com pivoteamento total):\n");
    for (i = 0; i < N; i++) {
        printf("x[%d] = %.2f\n", i, x[i]);
    }

    return 0;
}
