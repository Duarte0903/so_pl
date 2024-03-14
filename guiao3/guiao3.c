#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysystem.h"

// Exercício 1 - comando ls -l
int exec1() {
    execlp("ls", "ls", "-l", NULL);
    return 0;
}

// Exercício 2 - comando ls -l com processo filho
int exec2() {
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        execlp("ls", "ls", "-l", NULL);
    }

    if (pid < 0) {
        perror("Erro no fork");
        _exit(1);
    }

    else {
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Filho terminou com código %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

// Exercício 3 - versão simplificada da funcao system()
int exec3() {
    char comando1[] = "ls -l -a -h";
    char comando2[] = "sleeep 30";
	char comando3[] = "sleep 10";
	char comando4[] = "ps";
	int ret;

	printf("\nCOMANDO 1: a executar mysystem para %s\n",comando1);
	ret = mysystem(comando1);
	printf("COMANDO 1: ret = %d\n",ret);

	printf("\nCOMANDO 2: a executar mysystem para %s\n",comando2);
    ret = mysystem(comando2);
    printf("COMANDO 2: ret = %d\n",ret);

	printf("\nCOMANDO 3: a executar mysystem para %s\n",comando3);
	ret = mysystem(comando3);
    printf("COMANDO 3: ret = %d\n",ret);

    printf("\nCOMANDO 4: a executar mysystem para %s\n",comando4);
	ret = mysystem(comando4);
    printf("COMANDO 4: ret = %d\n",ret);

    return 0;
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "1") == 0) {
        exec1();
    }

    if (strcmp(argv[1], "2") == 0) {
        exec2();
    }

    if (strcmp(argv[1], "3") == 0) {
        exec3();
    }
}