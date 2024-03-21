#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void lookupNumber(int** matrix, int value, int* vector){
    pid_t pid;
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    for (int i = 0; i < ROWS; i++) {
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            close(fd[0]);

            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) {
                    write(fd[1], &i, sizeof(int));
                    printf("Sent: line %d\n", i);

                    close(fd[1]);
                    exit(0);
                }
            }

            close(fd[1]);
            exit(0);
        }
    }

    close(fd[1]);
    int index;

    while (read(fd[0], &index, sizeof(int)) > 0) {
        vector[index]++;
        printf("Received: line %d\n", index);
    }

    close(fd[0]);

    // Esperar que os filhos terminem
    for (int i = 0; i < ROWS; i++) {
        wait(NULL);
    }
}