#include <stdio.h>

// Função para encontrar a mediana de três elementos
int mediana_de_tres(int vetor[], int esquerda, int direita) {
    int meio = (esquerda + direita) / 2;

    // Encontrando os índices dos três elementos
    int a = vetor[esquerda];
    int b = vetor[meio];
    int c = vetor[direita];

    // Ordenando os índices dos elementos
    if ((a <= b && b <= c) || (c <= b && b <= a))
        return meio;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
        return esquerda;
    else
        return direita;
}

// Função de partição do quicksort
int particionar(int vetor[], int esquerda, int direita) {
    int indice_pivo = mediana_de_tres(vetor, esquerda, direita);
    int valor_pivo = vetor[indice_pivo];

    // Trocando o pivô com o último elemento do vetor
    vetor[indice_pivo] = vetor[direita];
    vetor[direita] = valor_pivo;

    int i = esquerda - 1;

    for (int j = esquerda; j < direita; j++) {
        if (vetor[j] <= valor_pivo) {
            i++;
            // Trocando elementos menores para a esquerda
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    // Colocando o pivô na posição correta
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[direita];
    vetor[direita] = temp;

    return i + 1;
}

// Função de ordenação rápida usando a mediana de três
void quicksort_mediana_de_tres(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        // Executando a partição
        int indice_pivo = particionar(vetor, esquerda, direita);

        // Recursivamente, ordenando as sub-listas
        quicksort_mediana_de_tres(vetor, esquerda, indice_pivo - 1);
        quicksort_mediana_de_tres(vetor, indice_pivo + 1, direita);
    }
}

int main() {
    int vetor[] = {3, 6, 8, 10, 1, 2, 1};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    quicksort_mediana_de_tres(vetor, 0, tamanho - 1);

    printf("Vetor ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
