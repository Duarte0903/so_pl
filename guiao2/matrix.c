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

// ex.5
int valueExists(int **matrix, int value) {
    int max_processes = 3;

    for (int p = 1; p <= max_processes; p++) {
        pid_t pid = fork();
        if (pid == 0) {
            for (int i = (p-1) * (ROWS/max_processes); i < p * (ROWS/max_processes); i++) {
                for (int j = 0; j < COLUMNS; j++) {
                    if (matrix[i][j] == value) {
                        printf("Value %d found in line %d, column %d\n", value, i, j);
                        _exit(1);
                    }
                }
            }
            _exit(0);
        }
    }

    int status;
    for (int i = 0; i < max_processes; i++) {
        wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 1) {
                return 1;
            }
        }
    }

    return 0;
}

// ex.6
void linesWithValue(int **matrix, int value) {
    int lines[ROWS];
    int max_processes = 3;

    for (int p = 1; p <= max_processes; p++) {
        pid_t pid = fork();
        if (pid == 0) {
            for (int i = (p-1) * (ROWS/max_processes); i < p * (ROWS/max_processes); i++) {
                for (int j = 0; j < COLUMNS; j++) {
                    if (matrix[i][j] == value) {
                        lines[i] = 1;
                        _exit(1);
                    }
                }
                lines[i] = 0;
            }
            _exit(0);
        }
    }

    int status;
    for (int i = 0; i < max_processes; i++) {
        wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 1) {
                printf("Line %d has the value %d\n", i, value);
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        if (lines[i] == 1) {
            printf("Line %d has the value %d\n", i, value);
        }
    }
}