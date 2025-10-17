#include <stdio.h>
#include <stdlib.h>

void imprimirSolucao(double *x, int n) {
    printf("Solucao:\n");
    for (int i = 0; i < n; i++) {
        printf("%.6f\n", x[i]);
    }
}

void eliminacaoDeGauss(double **A, double *b, int n) {
    for (int k = 0; k < n - 1; k++) {
        int maxRow = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > abs(A[maxRow][k])) {
                maxRow = i;
            }
        }

        if (maxRow != k) {
            // Trocar as linhas k e maxRow
            double *temp = A[k];
            A[k] = A[maxRow];
            A[maxRow] = temp;

            double tempB = b[k];
            b[k] = b[maxRow];
            b[maxRow] = tempB;
        }

        for (int i = k + 1; i < n; i++) {
            double fator = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= fator * A[k][j];
            }
            b[i] -= fator * b[k];
        }
    }

    double *x = malloc(n * sizeof(double));
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    imprimirSolucao(x, n);
    free(x);
}

int main() {
    int n = 20;

    double **A = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            if (i == j)
                A[i][j] = 1.0;
            else
                A[i][j] = 1.0 / (i + j + 1);
        }
    }

    double *b = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        b[i] = i + 1;
    }

    eliminacaoDeGauss(A, b, n);

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);

    return 0;
}


/* void Gauss_Escalonamento(int matriz[][21], int n) {
    int k, i, c, m[21][21];

    for (k = 1; k < n - 1; k++) {
        for (i = k + 1; i < n; i++) {
            m[i][k] = -matriz[i][k] / matriz[k][k];
            matriz[i][k] = 0;
            for (c = k + 1; c < n; c++) {
                matriz[i][c] = matriz[i][c] + m[i][k] * matriz[k][c];
            }
        }
    }
}
void Gauss_Parcial(int matriz[][21], int n){
    int k, temp, i, m, c, newtemp;
    
    for (k = 1; k < n - 1; k++){
        for (i = k+1; i < n; i++){
            temp = k;
            for(c = k+1; c < n; c++){
                if(abs(matriz[temp][k]) < abs(matriz[c][k])){
                    temp = c;
                }
            }
            if (temp != k){
                for (m = 0; m < n; m++){
                    newtemp = matriz[k][m];
                    matriz[k][m] = matriz[temp][m];
                    matriz[temp][m] = newtemp;
                }
            }
        }
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatriz(double A[][21], int n);
void LUfactorization(double A[][21], double b[], int n);

int main() {
    int n = 20;

    double A[21][21];
    double b[21];

    // Preenchendo a matriz A e o vetor b conforme a descrição do problema
    for (int i = 0; i <= n; i++) {
        b[i] = i + 1;
        for (int j = 0; j <= n; j++) {
            if (i <= j)
                A[i][j] = j - i;
            else
                A[i][j] = i - j;
        }
    }
     printMatriz(A, n);
    // Chamando a função de fatoração LU
    LUfactorization(A, b, n);

    // Imprimindo a matriz A após a fatoração LU
    printf("Matriz A apos a fatoracao LU:\n");
    printMatriz(A, n);

    return 0;
}

void printMatriz(double A[][21], int n) {
    printf("\n {\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf(" %.2f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n } \n");
}

void LUfactorization(double A[][21], double b[], int n) {
    for (int k = 0; k <= n; k++) {
        // Pivoteamento total
        int pivotRow = k;
        double pivotMax = fabs(A[k][k]);
        for (int i = k + 1; i <= n; i++) {
            if (fabs(A[i][k]) > pivotMax) {
                pivotRow = i;
                pivotMax = fabs(A[i][k]);
            }
        }

        // Troca de linhas
        if (pivotRow != k) {
            for (int j = 0; j <= n; j++) {
                double temp = A[pivotRow][j];
                A[pivotRow][j] = A[k][j];
                A[k][j] = temp;
            }
            double temp = b[pivotRow];
            b[pivotRow] = b[k];
            b[k] = temp;
        }

        // Eliminação de Gauss
        for (int i = k + 1; i <= n; i++) {
            double factor = A[i][k] / A[k][k];
            A[i][k] = factor;
            for (int j = k + 1; j <= n; j++) {
                A[i][j] -= factor * A[k][j];
            }
        }
    }
}

*/