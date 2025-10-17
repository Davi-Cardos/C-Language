#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define N 100

int* gerar_matriz_zero(int);

int main() 
{
    int i,j,k;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 

    int *matriz1 = (int *) malloc(N * N * sizeof(int));
    int *matriz2 = (int *) malloc(N * N * sizeof(int));
    int *matriz3 = gerar_matriz_zero(N);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matriz1[i * N + j] = rand() % 5;
            matriz2[i * N + j] = rand() % 5;
        }
    }
    gettimeofday(&tv1, &tz);
    
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                matriz3[i * N + j] += matriz1[i * N + k] * matriz2[k + N * j];
            }
        }
    }

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);
}
int* gerar_matriz_zero(int n)
{
    int i, j;

    int *matriz = (int *) malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matriz[i * n + j] = 0;
        }
    }
    
    return matriz;
}