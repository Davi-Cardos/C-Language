#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    char NomedoMeuAmor[8];
    char Amorzinho[8] = {'L','e','t','i','c','i','a','\0'};
    int resultado = 0;
    printf ("Digite o nome da pretendente: ");

    for (int i = 0; i < 8; i++){
        
        scanf("%c", &NomedoMeuAmor[i]);
    }

    for (int i=0; i <7; i++){
        if (NomedoMeuAmor[i] == Amorzinho[i]){
        resultado = resultado + 1;
    }
    else
    resultado = resultado - 1;
    }
    if (resultado == 7){
        printf ("Eh o meu Amorzinho, a gatinha mais gata de todos os universos, :)\n\n");
    }
    else 
    printf ("vc n eh o meu amor, vou te dar uma voadora \n \n :(");

    return 0;

}