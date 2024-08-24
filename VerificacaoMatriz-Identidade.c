#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define N 5000

int main()
{
    int i, j, k, cont = 0;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 

    int *matriz = (int *) malloc(N * N * sizeof(int));

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matriz[i * N + j] = rand() % 2;
        }
    }
    gettimeofday(&tv1, &tz);
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if(i == j && matriz[i * N + j] != 1){
                cont = 1;
            }
        }
    }
    if(cont == 0)
        printf("Eh uma matriz identidade\n"); 
    else 
        printf("Nao eh uma matriz identidade\n");
         
        

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);

    return 0;
}