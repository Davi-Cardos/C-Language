#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define N_FILOSOFOS 5
#define TEMPO_MAX 3.0  

omp_lock_t garfos[N_FILOSOFOS];

void pensar(int id) {
    printf("Filosofo %d esta pensando...\n", id);
    usleep(100000 + rand() % 300000);
}

void comer(int id) {
    printf("Filosofo %d esta comendo!\n\n", id);
    usleep(100000 + rand() % 300000);
}

int main() {
    srand(42);
    double inicio = omp_get_wtime();

    for (int i = 0; i < N_FILOSOFOS; i++)
        omp_init_lock(&garfos[i]);

    #pragma omp parallel num_threads(N_FILOSOFOS)
    {
        int id = omp_get_thread_num();
        int esquerda = id;
        int direita = (id + 1) % N_FILOSOFOS;
        double ultimo_tempo = omp_get_wtime();

        for (int i = 0; i < 5; i++) {
            pensar(id);

            double agora = omp_get_wtime();
            if (agora - ultimo_tempo > TEMPO_MAX) {
                printf("Filosofo %d ficou com fome demais! Forcando acesso aos garfos.\n", id);
                omp_set_lock(&garfos[esquerda]);
                omp_set_lock(&garfos[direita]);
            } else {
                if (esquerda < direita) {
                    omp_set_lock(&garfos[esquerda]);
                    omp_set_lock(&garfos[direita]);
                } else {
                    omp_set_lock(&garfos[direita]);
                    omp_set_lock(&garfos[esquerda]);
                }
            }

            comer(id);
            ultimo_tempo = omp_get_wtime();

            omp_unset_lock(&garfos[esquerda]);
            omp_unset_lock(&garfos[direita]);
        }
    }

    double fim = omp_get_wtime();
    printf("\nTempo total de execucao: %.4f segundos\n", fim - inicio);

    for (int i = 0; i < N_FILOSOFOS; i++)
        omp_destroy_lock(&garfos[i]);

    return 0;
}
