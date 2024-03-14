#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    valueExists(matrix, atoi(argv[1]));

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}