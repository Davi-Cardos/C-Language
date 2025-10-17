#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

// Macros para criar tabela de quantidade de bits em 1 em um byte
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define QUANT_BITS B6(0), B6(1), B6(1), B6(2)

// tabela de quantidade de bits em 1 em um byte.
const unsigned int __qbits_tab[256] = { QUANT_BITS };

// Função para contar cardinalidade da interseção
// a,b: ponteiros para vetores de bytes
// n: quantidade de bytes em cada vetor
static inline int card_inters(unsigned char *a, unsigned char *b, int nb) {
    int ret = 0;
    // percorre bytes dos vetores
    for (int i = 0; i < nb; i++)
        ret += __qbits_tab[a[i] & b[i]]; // i-ésimo byte
    return ret;
}

void simil(unsigned char *S, int n, unsigned char *a, int nb, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int card_i = card_inters(a, S + i, nb);
            int card_j = card_inters(a, S + j, nb);

            if (card_i < card_j) {
                // Troca os elementos
                unsigned char *temp = S + i;
                S[i] = S[j];
                S[j] = *temp;
            }
        }
    }
    // Reduz o tamanho do conjunto S para k elementos
    n = k;
    }

void print_conj(unsigned char *a, int nb) {
    printf("{");
    for (int b = 0, i = 0; b < nb; b++)
        for (int j = 0; j < 8; j++, i++) {
            char n = a[b] >> j;
            if (n & 1)
                printf(" %d", i);
        }
    printf(" }");
}

int main() {
    unsigned long long int mat = 20220003778; // Substitua pelo seu número de matrícula na UFRRJ
    int n = sizeof(unsigned long long int) << 8;
    unsigned long long int S[n];

    for (int i = 0, k = 0, l = 0; i < sizeof(unsigned long long int); i++, l += 8)
        for (unsigned long long int j = 0; j < 256; j++, k++)
            S[k] = mat & ~(~j << l);

    int L = 10;
    simil((unsigned char *) S, n, (unsigned char *) &mat, sizeof(unsigned long long int), L);
    printf("%d Conjuntos mais similares a %llu dentre os %d:\n", L, mat, n);
    print_conj((unsigned char *) &mat, sizeof(unsigned long long int));
    printf("\n-----------------------\n");

    for (int i = 0; i < L; i++) {
        printf("S[%d] = %llu\n", i, S[i]);
        print_conj((unsigned char *) (S + i), sizeof(unsigned long long int));
        printf("\n");
    }
    return 0;
}
