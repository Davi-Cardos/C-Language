#include <stdio.h>
#include <math.h>

double f(double t) {
    return 1 / (1 + t);
}

double trapezio_composto(double a, double b, int n);
double simpson_13(double a, double b, int n);
double simpson_38(double a, double b, int n);

int main() {
    double a = 1.0; 
    double b = 4.0; 
    int n = 300; // Número de subintervalos

    double resultado_trapezio = trapezio_composto(a, b, n);
    double resultado_simpson_13 = simpson_13(a, b, n);
    double resultado_simpson_38 = simpson_38(a, b, n);

    printf("Resultados:\n\n");
    printf("\tTrapézios Composta: %.6lf\n", resultado_trapezio);
    printf("\tSimpson 1/3 Composta: %.6lf\n", resultado_simpson_13);
    printf("\tSimpson 3/8 Composta: %.6lf\n", resultado_simpson_38);
    printf("\n");

    return 0;
}

double trapezio_composto(double a, double b, int n) {
    double h = (b - a) / n;
    double somatorio = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        double x_i = a + i * h;
        somatorio += f(x_i);
    }

    return h * somatorio;
}

double simpson_13(double a, double b, int n) {
    double h = (b - a) / n;
    double soma_funcao_simpson_13 = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x_i = a + i * h;
        soma_funcao_simpson_13 += (i % 2 == 0) ? 2 * f(x_i) : 4 * f(x_i);
    }

    return (h / 3) * soma_funcao_simpson_13;
}

double simpson_38(double a, double b, int n) {
    double h = (b - a) / n;
    double soma_funcao_simpson_38 = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x_i = a + i * h;
        soma_funcao_simpson_38 += (i % 3 == 0) ? 2 * f(x_i) : 3 * f(x_i);
    }

    return (3 * h / 8) * soma_funcao_simpson_38;
}
