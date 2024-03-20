/**
 * @file compactMatrix.c
 * @brief This file contains the implementation of a program that deals with compact matrices.
 *        A compact matrix is a matrix in which most of the elements are zero.
 *        This program performs operations on compact matrices such as addition, multiplication, and transposition.
 *        It also provides functions to display a compact matrix and check if it is symmetric.
 */
// 
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // Create a sparse matrix value
    unsigned int sparseMatrixX = 4;
    unsigned int sparseMatrixY = 5;
    int** dynamicSparseMatrix = (int**)malloc(sparseMatrixX * sizeof(int*));
    for (unsigned int index = 0; index < sparseMatrixX; index++)
        dynamicSparseMatrix[index] = (int*)malloc(sparseMatrixY * sizeof(int));
    
    // Designate the value to the dynamicSparseMatrix
    dynamicSparseMatrix[0] = (int[]){0, 0, 3, 0, 4};
    dynamicSparseMatrix[1] = (int[]){0, 0, 5, 7, 0};
    dynamicSparseMatrix[2] = (int[]){0, 0, 0, 0, 0};
    dynamicSparseMatrix[3] = (int[]){0, 2, 6, 0, 0};

    unsigned int nonZeroCount = 0;
    for (unsigned int x = 0; x < sparseMatrixX; x++) {
        for (unsigned int y = 0; y < sparseMatrixY; y++) {
            if (dynamicSparseMatrix[x][y] != 0) {
                nonZeroCount++;
            }
        }
    }

    // Based on the original matrix, create a new compact matrix dynamically
    int** dynamicCompactMatrix = (int**)malloc(nonZeroCount * sizeof(int*));
    for (unsigned int index = 0; index < nonZeroCount; index++)
        dynamicCompactMatrix[index] = (int*)malloc(3 * sizeof(int));

    // Designate the value to the dynamicCompactMatrix
    unsigned int compactMatrixRow = 0;
    for (unsigned int x = 0; x < sparseMatrixX; x++) {
        for (unsigned int y = 0; y < sparseMatrixY; y++) {
            if (dynamicSparseMatrix[x][y] != 0) {
                dynamicCompactMatrix[compactMatrixRow][0] = x;
                dynamicCompactMatrix[compactMatrixRow][1] = y;
                dynamicCompactMatrix[compactMatrixRow][2] = dynamicSparseMatrix[x][y];
                compactMatrixRow++;
            }
        }
    }

    // Print the dynamicCompactMatrix
    for (unsigned int x = 0; x < nonZeroCount; x++) {
        for (unsigned int y = 0; y < 3; y++) {
            printf("%d ", dynamicCompactMatrix[x][y]);
        }
        printf("\n");
    }

    // Free (sparesMatrix)
    for (unsigned int index = 0; index < nonZeroCount; index++)
        free(dynamicSparseMatrix[index]);
    free(dynamicSparseMatrix);

    // Free (dynamicSparseMatrix)
    for (unsigned int index = 0; index < nonZeroCount; index++)
        free(dynamicCompactMatrix[index]);
    free(dynamicCompactMatrix);

    return 0;
}
