#include <stdio.h>
#include <math.h>

#define N 2

int pesagem(int*, int, int, int, int);
int achaMoeda(int*, int, int);

int main()
{
	int inicio = 0;
	int fim = pow(3, N);
	
	//exemplo de entrada
	int D[] = {2, 2, 2, 2, 2, 1, 2, 2, 2};
	
	int indice = achaMoeda(D, inicio, fim - 1);
	
	printf("A moeda numero %d eh a falsa\n", indice + 1);
	
	return 0;
}
int achaMoeda(int *vet, int i, int f)
{
	if(i == f)
		return i;
		
	//*dividindo o vetor em tres partes iguais atraves da propriedade 3^N	
	int parte = (f - i + 1) / 3;
    int parte1_ini = i, parte1_fim = i + parte - 1;
    int parte2_ini = parte1_fim + 1, parte2_fim = parte1_fim + parte;
    int parte3_ini = parte2_fim + 1, parte3_fim = f;
    
    int res = pesagem(vet, parte1_ini, parte1_fim, parte2_ini, parte2_fim);
		
	//caso a primeira parte seja menor que a segunda, a moeda esta na primera	
	if(res == -1)
		return achaMoeda(vet, parte1_ini, parte1_fim);
		
	//caso a primeira parte seja maior que a segunda, a moeda esta na segunda
	if(res == 1)
		return achaMoeda(vet, parte2_ini, parte2_fim);
		
	//caso a primeira parte seja igual a segunda, a moeda esta na terceira
	else
		return achaMoeda(vet, parte3_ini, parte3_fim);
}
int pesagem(int *vet, int ai, int af, int bi, int bf){
	
	int soma1 = 0, soma2 = 0;
	
	for(int i = ai; i <= bf; i++){
		if(i <= af)
			soma1 += vet[i];
		else
			soma2 += vet[i];
	}
	if(soma1 < soma2)
		return -1;
	if(soma1 == soma2)
		return 0;
	return 1;
}
