#include <stdio.h>

// Função para calcular a integral pelo método dos trapézios composta
double trapezoidal(double x[], double y[], int n) {
    double h = x[1] - x[0]; // Intervalo
    double integral = 0.0;

    // Aplicando a fórmula do método dos trapézios composta
    for (int i = 1; i < n - 1; i++) {
        integral += 2 * y[i];
    }
    integral += y[0] + y[n - 1];
    integral *= h / 2.0;

    return integral;
}

int main() {
    // Valores fornecidos
    double x[] = {0.0, 0.25, 0.5, 0.75, 1.0};
    double y[] = {1.000, 1.284, 1.649, 2.117, 2.718};
    int n = sizeof(x) / sizeof(x[0]);

    double result = trapezoidal(x, y, n);

    printf("A integral aproximada usando o método dos trapézios composta é: %f\n", result);

    return 0;
}