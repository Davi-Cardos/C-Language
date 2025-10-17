#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fazmatriz(int a, int b, int matriz[a][b]){
    int k = 0;

    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            matriz[i][j] = k;
            k++;
        }
    }
}

int main (void){
    int ma[3][5];

    fazmatriz(3, 5, ma);

    printf("Matrix:\n");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 5; j++){
            printf("%d ", ma[i][j]);
        }
        printf("\n");
    }

    return 0;
}
