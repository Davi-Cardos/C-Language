#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void troca_linha(double A[][21], int troca1, int troca2, int n) {
    for (int j = 0; j <= n; j++) {
        double temp = A[troca1][j];
        A[troca1][j] = A[troca2][j];
        A[troca2][j] = temp;
    }
}

void LU_Fatorizacao(double A[][21], int n) {
    for (int k = 0; k < n; k++) {
        double maxVal = 0.0;
        int pivolinha = k;
        int pivocoluna = k;
        
        // encontrando o pivo
        for (int i = k; i < n; i++) {
            for (int j = k; j < n; j++) {
                if (fabs(A[i][j]) > maxVal) {
                    maxVal = fabs(A[i][j]);
                    pivolinha = i;
                    pivocoluna = j;
                }
            }
        }
        
        if (maxVal == 0) {
            printf("nao eh possivel ser fatorada LU com pivoteamento total.\n");
            return;
        }
        
        // trocalinha
        if (pivolinha != k) {
            troca_linha(A, pivolinha, k, n);
        }
        
        // trocacoluna
        if (pivocoluna != k) {
            for (int i = 0; i < n; i++) {
                double temp = A[i][pivocoluna];
                A[i][pivocoluna] = A[i][k];
                A[i][k] = temp;
            }
        }
        
        // fatorando LU
        for (int i = k + 1; i < n; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}

void solucao_Sistema(double A[][21], double b[], double x[], int n) {
    // (Ly = b)
    for (int i = 0; i < n; i++) {
        x[i] = b[i];
        for (int j = 0; j < i; j++) {
            x[i] -= A[i][j] * x[j];
        }
    }
    
    // (Ux = y)
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void inversa(double A[][21], double inverse[][21], int n) {
    double b[21], x[21];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[j] = (i == j) ? 1.0 : 0.0;
        }
        
        solucao_Sistema(A, b, x, n);
        
        for (int j = 0; j < n; j++) {
            inverse[j][i] = x[j];
        }
    }
}

int main() {
    double A[21][21] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        {2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18},
        {3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
        {4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
        {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        {6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
        {7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
        {8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8},
        {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7},
        {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6},
        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5},
        {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4},
        {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3},
        {18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2},
        {19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1},
        {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
    };
    
    double b[21] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    double x[21];
    
    //chamando as funcoes

    LU_Fatorizacao(A, 21);
    
    solucao_Sistema(A, b, x, 21);
    
    printf("Solucao do sistema linear Ax = b:\n");
    for (int i = 0; i < 21; i++) {
        printf("x[%d] = %.2f\n", i, x[i]);
    }
    
    double inverse[21][21];
    inversa(A, inverse, 21);
    
    //printando resultado

    printf("\nMatriz inversa de A:\n{\n");
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            printf(" %.2f ", inverse[i][j]);
        }
        printf("\n");
    }
    printf("}\n");
    return 0;
}
