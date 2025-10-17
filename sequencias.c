#include <stdio.h>
int main (void){

    char texto[100], freq[100];
    int i, c, n, k;

    scanf (" %[^\n]s", texto);

    n = 0;

    for (i = 0; texto[i] != '\0'; i++){
        if (texto[i] >= 'A' && texto[i] <= 'Z'){
            texto[i] = texto[i] + 32;
        }
    }

    printf ("%s\n", texto);

    for (i = 0; i < 100; i++){
        freq[i] = '\0';
    }

    k = 0;

    for (i = 0; texto[i] != '\0'; i++){
        for(c = 0; texto[c] != '\0'; i++){
            if (texto[c] == texto[i] && c != i){
                freq[k] = texto[c];
                n++;
                k++;
            }
        }

    }

    printf ("%s", freq);


    for (i = 0; i < (n - 1); i++){
        for (c = 0; c < n; c++){
            if (freq[c] == freq[i] && c != i){
                freq[c] = '1';
            }
        }
    }

    printf ("%s", freq);

    return 0;
}