#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <pthread.h>
#include <sys/time.h>

#define N 3000

int** gerar_matriz(int);
int** gerar_matriz_zero(int);

int main()
{
    int i, j, k, aux;

    int **matriz1 = gerar_matriz(N);
    int **matriz2 = gerar_matriz(N);
    int **matriz3 = gerar_matriz_zero(N);

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            matriz1[i][j] = rand() % 5;
            matriz2[i][j] = rand() % 5;
        }
    }
	 
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 

    gettimeofday(&tv1, &tz);
    
    for(i=0; i < N; i++){
        for(j=0; j < N; j++){
            aux = 0;
            for(k=0; k < N; k++){
                aux += matriz1[i][k] * matriz2[k][j];
            }
            matriz3[i][j] = aux;
        }
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);

    return 0;
}
int** gerar_matriz(int n)
{
	int **matriz;
    int i;

    matriz = (int **) malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matriz[i] = (int *) malloc(n * sizeof(int));
    }
    return matriz;
}
int** gerar_matriz_zero(int n)
{
	int **matriz;
    int i, j;

    matriz = (int **) malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matriz[i] = (int *) malloc(n * sizeof(int));
    }
    
    return matriz;
}