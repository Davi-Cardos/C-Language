#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(char *command) {
    // Dividir o comando em tokens
    char *tokens[MAX_COMMAND_LENGTH];
    int i = 0;
    tokens[i] = strtok(command, " ;");
    
    while (tokens[i] != NULL) {
        i++;
        tokens[i] = strtok(NULL, " ;");
    }
    
    // Criar um processo filho
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo filho
        execvp(tokens[0], tokens);
        // Se execvp falhar, exibe uma mensagem de erro
        perror("Erro ao executar o comando");
        exit(EXIT_FAILURE);
    } else {
        // Processo pai
        wait(NULL); // Espera pelo término do processo filho
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Exibir o prompt
        printf(">> ");
        // Obter o comando do usuário
        fgets(command, sizeof(command), stdin);

        // Remover o caractere de nova linha
        command[strcspn(command, "\n")] = '\0';

        // Verificar se o comando é "exit" para encerrar o shell
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Executar o comando
        execute_command(command);
    }

    return 0;
}
