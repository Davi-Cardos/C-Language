#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <omp.h>

int main() {
    unsigned long D, N;
    if (scanf("%lu %lu", &D, &N) != 2) {
        printf("Erro: entrada invalida.\n");
        return 1;
    }
    unsigned long bits = (unsigned long)(D * log2(10)) + 128;
    mpf_t soma_total;
    mpf_init2(soma_total, bits);
    mpf_set_ui(soma_total, 0);
    #pragma omp parallel
    {
        mpf_t soma_local, termo, temp;
        mpf_init2(soma_local, bits);
        mpf_init2(termo, bits);
        mpf_init2(temp, bits);
        mpf_set_ui(soma_local, 0);
        #pragma omp for schedule(dynamic, 10000)
        for (unsigned long i = 1; i <= N; i++) {
            mpf_set_ui(temp, i);
            mpf_ui_div(termo, 1, temp);
            mpf_add(soma_local, soma_local, termo);
        }
        #pragma omp critical
        {
            mpf_add(soma_total, soma_total, soma_local);
        }
        mpf_clear(soma_local);
        mpf_clear(termo);
        mpf_clear(temp);
    }
    gmp_printf("%.*Ff\n", D, soma_total);

    mpf_clear(soma_total);

    return 0;
}
