#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_PONTOS 4

typedef struct {
    double x, y;
} Ponto;

typedef struct {
    double x, y;
    double metadeLargura, metadeAltura;
} Retangulo;

typedef struct Quadtree {
    Retangulo limite;
    Ponto* pontos;
    int numPontos;
    int dividido;
    struct Quadtree *NE, *NO, *SE, *SO;
} Quadtree;

int contem(Retangulo r, Ponto p) {
    return (p.x >= r.x - r.metadeLargura &&
            p.x <= r.x + r.metadeLargura &&
            p.y >= r.y - r.metadeAltura &&
            p.y <= r.y + r.metadeAltura);
}

int intersecta(Retangulo a, Retangulo b) {
    return !(b.x - b.metadeLargura > a.x + a.metadeLargura ||
             b.x + b.metadeLargura < a.x - a.metadeLargura ||
             b.y - b.metadeAltura > a.y + a.metadeAltura ||
             b.y + b.metadeAltura < a.y - a.metadeAltura);
}

Quadtree* criarQuadtree(Retangulo limite) {
    Quadtree* q = (Quadtree*) malloc(sizeof(Quadtree));
    q->limite = limite;
    q->pontos = (Ponto*) malloc(sizeof(Ponto) * MAX_PONTOS);
    q->numPontos = 0;
    q->dividido = 0;
    q->NE = q->NO = q->SE = q->SO = NULL;
    return q;
}

void subdividir(Quadtree* q) {
    double x = q->limite.x;
    double y = q->limite.y;
    double w = q->limite.metadeLargura / 2.0;
    double h = q->limite.metadeAltura / 2.0;
    q->NE = criarQuadtree((Retangulo){x + w, y - h, w, h});
    q->NO = criarQuadtree((Retangulo){x - w, y - h, w, h});
    q->SE = criarQuadtree((Retangulo){x + w, y + h, w, h});
    q->SO = criarQuadtree((Retangulo){x - w, y + h, w, h});
    q->dividido = 1;
}

int inserir(Quadtree* q, Ponto p) {
    if (!contem(q->limite, p)) return 0;
    if (q->numPontos < MAX_PONTOS && !q->dividido) {
        q->pontos[q->numPontos++] = p;
        return 1;
    }
    if (!q->dividido) subdividir(q);
    if (inserir(q->NE, p)) return 1;
    if (inserir(q->NO, p)) return 1;
    if (inserir(q->SE, p)) return 1;
    if (inserir(q->SO, p)) return 1;
    return 0;
}

void consultar(Quadtree* q, Retangulo area, Ponto* resultados, int* count) {
    if (!intersecta(q->limite, area)) return;
    for (int i = 0; i < q->numPontos; i++) {
        if (contem(area, q->pontos[i])) {
            #pragma omp critical
            {
                resultados[*count] = q->pontos[i];
                (*count)++;
            }
        }
    }
    if (q->dividido) {
        #pragma omp task shared(resultados, count)
        consultar(q->NE, area, resultados, count);
        #pragma omp task shared(resultados, count)
        consultar(q->NO, area, resultados, count);
        #pragma omp task shared(resultados, count)
        consultar(q->SE, area, resultados, count);
        #pragma omp task shared(resultados, count)
        consultar(q->SO, area, resultados, count);
    }
    #pragma omp taskwait
}

void liberarQuadtree(Quadtree* q) {
    if (!q) return;
    if (q->dividido) {
        liberarQuadtree(q->NE);
        liberarQuadtree(q->NO);
        liberarQuadtree(q->SE);
        liberarQuadtree(q->SO);
    }
    free(q->pontos);
    free(q);
}

int main() {
    int N;
    printf("Quantos pontos deseja inserir? ");
    scanf("%d", &N);
    Retangulo regiao = {0, 0, 50, 50};
    Quadtree* qt = criarQuadtree(regiao);
    Ponto* pontos = (Ponto*) malloc(sizeof(Ponto) * N);
    printf("Digite os pontos (x y):\n");
    for (int i = 0; i < N; i++) scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
    double inicio = omp_get_wtime();
    for (int i = 0; i < N; i++) inserir(qt, pontos[i]);
    double fimConstrucao = omp_get_wtime();
    Retangulo sub = {0, 0, 20, 20};
    Ponto resultados[1000];
    int count = 0;
    #pragma omp parallel
    {
        #pragma omp single
        consultar(qt, sub, resultados, &count);
    }
    double fimConsulta = omp_get_wtime();
    printf("\nPontos dentro da sub-regiao (%.1f, %.1f, %.1f, %.1f):\n",
           sub.x, sub.y, sub.metadeLargura, sub.metadeAltura);
    for (int i = 0; i < count; i++)
        printf("(%.2f, %.2f)\n", resultados[i].x, resultados[i].y);
    printf("\nTempo de construcao: %.6fs\n", fimConstrucao - inicio);
    printf("Tempo de consulta: %.6fs\n", fimConsulta - fimConstrucao);
    liberarQuadtree(qt);
    free(pontos);
    return 0;
}
