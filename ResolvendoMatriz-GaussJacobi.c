#include <stdio.h>
#include <math.h>

#define N 20
#define H 0.1
#define PARADA 1e-4

void gaussJacobi() {
    double x[N + 2] = {0};  // Vetor solução inicial (todos os elementos são 0)
    double x_new[N + 2];

    int iterations = 0;
    double error = PARADA + 1.0;

    while (error > PARADA) {
        error = 0.0;

        // Atualiza cada elemento do vetor x_new usando a fórmula do método de Gauss-Jacobi
        for (int i = 1; i <= N; i++) {
            x_new[i] = (1 - x[i - 1] - x[i + 1]) / (-2 * (1 + H * H));
            error += fabs(x_new[i] - x[i]);
        }

        // Copia os novos valores para o vetor x
        for (int i = 1; i <= N; i++) {
            x[i] = x_new[i];
        }

        iterations++;
    }

    printf("Gauss-Jacobi:\n");
    printf("Numero de iteracoes: %d\n", iterations);
    printf("Solucao aproximada:\n");
    for (int i = 1; i <= N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }
}

void gaussSeidel() {
    double x[N + 2] = {0};  // Vetor solução inicial (todos os elementos são 0)

    int iterations = 0;
    double error = PARADA + 1.0;

    while (error > PARADA) {
        error = 0.0;

        // Atualiza cada elemento do vetor x usando a fórmula do método de Gauss-Seidel
        for (int i = 1; i <= N; i++) {
            double x_new = (1 - x[i - 1] - x[i + 1]) / (-2 * (1 + H * H));
            error += fabs(x_new - x[i]);
            x[i] = x_new;
        }

        iterations++;
    }

    printf("\nGauss-Seidel:\n");
    printf("Numero de iteracoes: %d\n", iterations);
    printf("Solucao aproximada:\n");
    for (int i = 1; i <= N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }
}

void SOR() {
    double x[N + 2] = {0};  // Vetor inicial (todos os elementos são 0)

    double omega = 1.5;  // Fator de relaxação (w)

    int iterations = 0;
    double error = PARADA + 1.0;

    while (error > PARADA) {
        error = 0.0;

        // Atualiza cada elemento do vetor x usando a fórmula do método SOR
        for (int i = 1; i <= N; i++) {
            double x_new = (1 - x[i - 1] - x[i + 1]) / (-2 * (1 + H * H));
            x_new = omega * x_new + (1 - omega) * x[i];
            error += fabs(x_new - x[i]);
            x[i] = x_new;
        }

        iterations++;
    }

    printf("\nSOR (omega = %.2f):\n", omega);
    printf("Numero de iteracoes: %d\n", iterations);
    printf("Solucao aproximada:\n");
    for (int i = 1; i <= N; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }
}

int main() {
    //chamando as funcoes
    
    gaussJacobi();
    gaussSeidel();
    SOR();

    return 0;
}
