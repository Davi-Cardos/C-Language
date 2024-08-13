#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void bissecao (double (*f) (double), double x_0, double x_1, double erro, double derivada_a, double derivada_b);
void secante (double (*f) (double), double x_0, double x_1, double erro, double derivada_a, double derivada_b);
double derivada (double (*f) (double), double x_0, double erro);
double f1(double x);
double f2(double x);
double f3(double x);

int main (int argc, char *argv[]){

    double x_0, x_1, derivada_b, derivada_a;
    double erro;

    if (strcmp(argv[1], "bs") == 0){
        printf ("bissecao acorda ai \n");

        erro = atof(argv[2]);
        x_0 = atof (argv[3]);
        x_1 = atof (argv[4]);

        printf ("Funcao letra a:\n\n");

        derivada_a = derivada (f1, x_0, erro);
        derivada_b = derivada (f1, x_1, erro);
        bissecao (f1, x_0, x_1, erro, derivada_a, derivada_b);

        printf ("\n*************\n");

        printf ("Funcao letra b:\n\n");

        derivada_a = derivada (f2, x_0, erro);
        derivada_b = derivada (f2, x_1, erro);
        bissecao (f2, x_0, x_1, erro, derivada_a, derivada_b);

        printf ("\n*************\n");

        printf ("funcao letra c:\n\n");

        derivada_a = derivada (f3, x_0, erro);
        derivada_b = derivada (f3, x_1, erro);
        bissecao (f2, x_0, x_1, erro, derivada_a, derivada_b);
        

        
            
        } else if (strcmp(argv[1], "se") == 0){
        printf ("secante acorda ai\n");

        erro = atof(argv[2]);
        x_0 = atof (argv[3]);
        x_1 = atof (argv[4]);

        printf("Metodo Secante na funcao letra a:\n\n");
        derivada_a = derivada (f1, x_0, erro);
        derivada_b = derivada (f1, x_1, erro);

       secante (f1, x_0, x_1, erro, derivada_a, derivada_b);

        printf ("\n*************\n");

        printf("Metodo Secante na funcao letra b:\\nn");
        derivada_a = derivada (f2, x_0, erro);
        derivada_b = derivada (f2, x_1, erro);

       secante (f2, x_0, x_1, erro, derivada_a, derivada_b);

        printf ("\n*************\n");

        printf("Metodo Secante na funcao letra c:\n\n");
        derivada_a = derivada (f3, x_0, erro);
        derivada_b = derivada (f3, x_1, erro);

       secante (f3, x_0, x_1, erro, derivada_a, derivada_b);
    }
    
    else {
            printf("Digitou errado, erro\n");
        }
        return 0;
    }



// funcoes
double f1(double x) {
    return pow(x, 5) - 2*pow(x, 4) - 9*pow(x, 3) + 22*pow(x, 2) + 4*x - 24;
}

double f2(double x) {
    return sqrt(x) - cos(x);
}

double f3(double x) {
    return (x - 5) * exp(-x);
}

// Metodo da Bissecao pegando o algoritmo dos slides e implementando pro C com alteracoes para sair da forma que o exercicio pede
void bissecao (double (*f)(double), double a, double b, double erro, double derivada_a, double derivada_b) {
    double c = a;
    int contador = 0, tem_raiz;
    double funcao_a, funcao_b;
    funcao_a = f(a);
    funcao_b = f(b);

    //os prints de saida com o valor das variaveis iniciais e das funcoes e derivadas com esses valores conforme o exercicio pede
    printf ("Zero da funcao - metodos implemntados em C\n Metodo: bs \n Refinamento e Criterio de Parada: %e \n Erro Max: %e \n x(0) ou a = %lf \n x(1) ou b = %lf \n\n *****Metodo da Bissecao***** \nError: %e", erro, erro, a, b, erro);
    printf ("\nIntervalo: (%lf, %lf) \n", a, b);
    printf ("fx (a = %lf) = %lf\nfx (b = %lf) = %lf\n ", a, funcao_a, b, funcao_b); 
    printf ("Informacao da derivada\ngx(a = %lf) = %lf\ngx(b = %lf) = %lf\n", a, derivada_a, b, derivada_b);

    while ((b - a) >= erro) {
        contador++;

        c = (a+b)/2;
        // eh raiz ou nao, aqui se descobre ate encontrar ou o laço acabar
        if (f(c) == 0.0){
            tem_raiz = 1;
            break;
        }

        if (f(c)*f(a) < 0){
            b = c;
        }

        else{
            a = c;
        }    
    }

    if(tem_raiz == 1){
        printf ("TEM RAIZ REAL\n");
        printf ("O valor de x eh: %lf - passos da interacao: %d", c, contador);
    }
    else{
        printf ("NAO TEM RAIZ REAL - passos da intracao: %d \n", contador);
    }

    

}
 
// Metodo da Secante pegando o algoritmo dos slides e implementando pro C com alteracoes para sair da forma que o exercicio pede
void secante (double (*f)(double), double x_0, double x_1, double erro, double derivada_a, double derivada_b) {
    double x_2 = x_1 - (f(x_1) * (x_1 - x_0)) / (f(x_1) - f(x_0));
    double funcao_x_0 = f(x_0);
    double funcao_x_1 = f(x_1);
    int contador = 0;

    //os prints de saida com o valor das variaveis iniciais e das funcoes e derivadas com esses valores conforme o exercicio pede
    printf ("Zero da funcao - metodos implemntados em C\n Metodo: se \n Refinamento e Criterio de Parada: %e \n Erro Max: %e \n x(0) ou a = %lf \n x(1) ou b = %lf \n\n *****Metodo da Secante***** \nError: %e", erro, erro, x_0, x_1, erro);
    printf ("\nIntervalo: (%lf, %lf) \n", x_0, x_1);
    printf ("fx (a = %lf) = %lf\nfx (b = %lf) = %lf\n ", x_0, funcao_x_0, x_1, funcao_x_1); 
    printf ("Informacao da derivada\ngx(a = %lf) = %lf\ngx(b = %lf) = %lf\n", x_0, derivada_a, x_1, derivada_b);

    while (fabs(x_2 - x_1) > erro) {
        contador++;
        x_0 = x_1;
        x_1 = x_2;
        x_2 = x_1 - (f(x_1) * (x_1 - x_0)) / (f(x_1) - f(x_0));
    }
    //vendo se entrou no laço, ou seja, se o EA (erro absoluto) eh maior que o erro de parada
    if (contador == 0){
        printf ("Nao eh possivel fazer o metodo\n");
    }
    else{
    printf ("O valor de x eh: %lf - passos da interacao: %d\n", x_2, contador);
    }
}

double derivada (double (*f) (double), double x_0, double erro){
return (f(x_0 + erro) - f(x_0)) / erro;

}
