#include "mysystem.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {
	int res = -1;
	pid_t pid = fork();
	int status;
	
	char args[10][20];
    char *command_name = NULL;

    char *token = strtok((char*)command, " ");
    int i = 0;
    while (token != NULL) {
        if (i == 0) {
            command_name = token; 
        } else {
            strcpy(args[i - 1], token);
        }
        token = strtok(NULL, " ");
        i++;
    }

	if (pid == 0) {
		execvp(command_name, (char* const*)args);
		_exit(EXIT_FAILURE);
	}

	if (pid < 0) {
		perror("Erro no fork");
		_exit(1);
	}

	else {
		wait(&status);
		if (WIFEXITED(status)) {
			res = WEXITSTATUS(status);
		}
	}

	return res;
}