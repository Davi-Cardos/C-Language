#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h> 

#define BUFFER_SIZE 5  
#define NUM_CONSUMERS 2 

int buffer[BUFFER_SIZE];
int count = 0;  
static int producao_encerrada = 0;
int main() {
    double inicio = omp_get_wtime();
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel num_threads(NUM_CONSUMERS + 1)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) { 
            for (int i = 1; i <= 10; i++) {
                omp_set_lock(&lock);

                if (count < BUFFER_SIZE) {
                    buffer[count++] = i;
                    printf("[PRODUTOR] produziu item %d (total no buffer = %d)\n", i, count);
                } else {
                    printf("[PRODUTOR] buffer cheio! aguardando...\n");
                }

                omp_unset_lock(&lock);
                sleep(1); 
            }
        } else { 
    while (1) {
        omp_set_lock(&lock);
        if (count > 0) {
            int item = buffer[--count];
            printf("Consumidor %d consumiu item %d (restam %d no buffer)\n", tid, item, count);
            omp_unset_lock(&lock);
            sleep(2);
        } else {
            if (producao_encerrada) {
                omp_unset_lock(&lock);
                break;
            }
            omp_unset_lock(&lock);
            sleep(1);
        }
        #pragma omp flush(count)
        if (count == 0 && omp_get_thread_num() != 0) {
            producao_encerrada = 1;
        }
    }
}
    }
     double fim = omp_get_wtime();

    printf("Tempo total de execucao: %.2f segundos\n", fim - inicio);
    omp_destroy_lock(&lock);
    printf("\nExecucao finalizada \n");
    return 0;
}
