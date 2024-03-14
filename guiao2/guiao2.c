#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

int exec1() {
    printf("O processo %d é filho do processo %d\n", getpid(), getppid());
    return 0;
}

int exec2() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("O processo %d é filho do processo %d\n", getpid(), getppid());
    } else {
        printf("O meu pid é %d e o pid do meu filho é %d\n", getpid(), pid);
    }

    return 0;
}

int exec3() {
    int status;
    for (int i = 1; i <= 10; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("O processo %d é filho do processo %d\n", getpid(), getppid());
            _exit(i+1);
        }
        /* pai */
        pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("pai %d: filho %d, %d\n", getpid(), pid, WEXITSTATUS(status));
        }
    }

    return 0;
}

int exec4() {
    for (int i = 0; i != 10; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("O processo %d é filho do processo %d\n", getpid(), getppid());
            return i+1;
        }
    }

    int status;
    for (int i = 0; i != 10; i++) {
        pid_t pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("pai %d: filho %d, %d\n", getpid(), pid, WEXITSTATUS(status));
        }
    }

    return 0;
}

int exec5(int find) {
    int **matrix = createMatrix();

    printMatrix(matrix);

    valueExists(matrix, find);

    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

int exec6(int find) {
    int **matrix = createMatrix();

    printMatrix(matrix);

    linesWithValue(matrix, find);

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

    if (strcmp(argv[1], "4") == 0) {
        exec4();
    }

    if (strcmp(argv[1], "5") == 0) {
        exec5(atoi(argv[2]));
    }

    if (strcmp(argv[1], "6") == 0) {
        exec6(atoi(argv[2]));
    }

    return 0;
}