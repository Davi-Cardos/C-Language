#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char cmd[100], command[100], *parameters[20];
    char *envp[] = { (char *) "PATH=/bin", 0 };
    while(1) {
        // Prompt
        printf(">> ");

        // Lê o comando do terminal
        fgets(cmd, sizeof(cmd), stdin);

        // Remove o '\n' do final do comando
        cmd[strlen(cmd) - 1] = '\0';

        // Se o usuário digitou "exit", o shell termina
        if(strcmp(cmd, "exit") == 0) 
            break;

        // Separa o comando e os parâmetros
        char *token = strtok(cmd, " ");
        int i = 0;
        while(token != NULL) {
            parameters[i] = malloc(strlen(token) + 1);
            strcpy(parameters[i], token);
            token = strtok(NULL, " ");
            i++;
        }
        parameters[i] = NULL;

        // Cria um processo filho para executar o comando
        pid_t pid = fork();

        if(pid == 0) {
            // Processo filho
            strcpy(command, "/bin/");
            strcat(command, parameters[0]);
            execve(command, parameters, envp);
        } else {
            // Processo pai
            wait(NULL);
        }
    }

    return 0;
}