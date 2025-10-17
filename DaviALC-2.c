#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void trocalinha(double A[][21], int linha1, int linha2, int n) {
    for (int j = 0; j <= n; j++) {
        double temp = A[linha1][j];
        A[linha1][j] = A[linha2][j];
        A[linha2][j] = temp;
    }
}

void LU_Fatorizacao(double A[][21], int n) {
    for (int k = 0; k < n; k++) {
        double maxVal = 0.0;
        int pivolinha = k;
        int pivocoluna = k;
        
        // Find the pivot element
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
        
        // trocalinha se necessario
        
        if (pivolinha != k) {
            trocalinha(A, pivolinha, k, n);
        }
        
        // troca coluna
        if (pivocoluna != k) {
            for (int i = 0; i < n; i++) {
                double temp = A[i][pivocoluna];
                A[i][pivocoluna] = A[i][k];
                A[i][k] = temp;
            }
        }
        
        // LU fatorizacao
        for (int i = k + 1; i < n; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
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
    
    LU_Fatorizacao(A, 21);
    
    printf("Matriz L:\n");
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (i > j)
                printf("%.2f ", A[i][j]);
            else if (i == j)
                printf("1.00 ");
            else
                printf("0.00 ");
        }
        printf("\n");
    }
    
    printf("\nMatriz U:\n");
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (i <= j)
                printf("%.2f ", A[i][j]);
            else
                printf("0.00 ");
        }
        printf("\n");
    }

    printf("\n Nova Matriz A\n");
    for (int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            printf(" %2.lf ", A[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
