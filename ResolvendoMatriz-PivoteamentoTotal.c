#include <stdio.h>
#include <stdlib.h>

void printMatriz(double A[][21], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", A[i][j]);
        }
        printf("\n");
    }
}

void trocalinha(double A[][21], int linha1, int linha2, int n) {
    for (int j = 0; j < n; j++) {
        double temp = A[linha1][j];
        A[linha1][j] = A[linha2][j];
        A[linha2][j] = temp;
    }
}

void LU_Fatorizacao(double A[][21], int n) {
    for (int k = 0; k < n; k++) {
        double maxVal = 0.0;
        int pivolinha = k;
        for (int i = k; i < n; i++) {
            if (abs(A[i][k]) > maxVal) {
                maxVal = abs(A[i][k]);
                pivolinha = i;
            }
        }
        if (maxVal == 0) {
            printf("nao eh possivel ser fatorada LU com pivoteamento total.\n");
            return;
        }
        if (pivolinha != k) {
            trocalinha(A, pivolinha, k, n);
        }
        for (int i = k + 1; i < n; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}

int main() {
    double A[21][21];
    int n = 21;

    // Inicializar matriz A

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                A[i][j] = j - i;
            } else {
                A[i][j] = i - j;
            }
        }
    }

    //chamando as funcoes

    printf("Matriz A original:\n");
    printMatriz(A, n);

    LU_Fatorizacao(A, n);

    printf("\nMatriz A apos a fatoracao LU com pivoteamento total:\n");
    printMatriz(A, n);

    return 0;
}
