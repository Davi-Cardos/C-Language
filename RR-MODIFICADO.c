#include <stdio.h>
#include <stdlib.h>

int menor_processo(int bt[], int arrt[], int total, int n);

int main()
{
    // Entrada do número de processos
    int n;
    FILE *arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fscanf(arquivo, "%d", &n);
    int tempo_espera = 0, tempo_turnaround = 0, tempo_chegada[n], tempo_execucao[n], tempo_execucao_temp[n];
    int x = n;

    // Entrada dos detalhes dos processos
    for (int i = 0; i < n; i++)
    {
        fscanf(arquivo, "%d %d", &tempo_chegada[i], &tempo_execucao[i]);
        tempo_execucao_temp[i] = tempo_execucao[i];
    }

    // Entrada do quantum (intervalo de tempo)
    int quantum;
    fscanf(arquivo, "%d", &quantum);

    // Total indica o tempo total, contador indica qual processo está sendo executado
    int total = 0, contador = 0, i;
    float tr_tx = 0.0, total_tempo_execucao = 0.0;
    printf("ID do Processo    Tempo de Execucao   Tempo de Turnaround   Tempo de Espera\n");
    for (total = 0, i = 0; x != 0;)
    {
        // Define as condições
        if (tempo_execucao_temp[i] <= quantum && tempo_execucao_temp[i] > 0)
        {
            total = total + tempo_execucao_temp[i];
            tempo_execucao_temp[i] = 0;
            contador = 1;
        }
        else if (tempo_execucao_temp[i] > 0)
        {
            tempo_execucao_temp[i] = tempo_execucao_temp[i] - quantum;
            total += quantum;
        }
        if (tempo_execucao_temp[i] == 0 && contador == 1)
        {
            x--; // Decrementa o número de processos
            printf("\nProcesso No %d  \t\t %d\t\t\t%d\t\t  %d", i + 1, tempo_execucao[i],
                   total - tempo_chegada[i], total - tempo_chegada[i] - tempo_execucao[i]);
            tempo_espera = tempo_espera + total - tempo_chegada[i] - tempo_execucao[i];
            tempo_turnaround += total - tempo_chegada[i];
            contador = 0;
            total_tempo_execucao += tempo_execucao[i];
        }

        i = menor_processo(tempo_execucao_temp, tempo_chegada, total, n);

    }

    float media_tempo_espera = tempo_espera * 1.0 / n;
    float media_tempo_turnaround = tempo_turnaround * 1.0 / n;
    tr_tx = tempo_turnaround / total_tempo_execucao;
    printf("\nTempo Medio de Espera: %f", media_tempo_espera);
    printf("\nTempo Medio de Turnaround: %f", media_tempo_turnaround);
    printf("\nTr/Tx: %f", tr_tx);
    return 0;
}
int menor_processo(int bt[], int arrt[], int total, int n){
    int menor = total * 10, index;

    for(int i = 0; i < n; i++){
        if(bt[i] < menor && arrt[i] <= total && bt[i] > 0){
            index = i;
            menor = bt[index];
        }
    }
    return index;
}