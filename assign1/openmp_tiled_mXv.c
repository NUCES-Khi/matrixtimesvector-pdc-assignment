#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TILE_SIZE 16

// Function to allocate memory for matrix
double** allocateMatrix(int rows, int cols) {
    double** mat = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat[i] = (double*)malloc(cols * sizeof(double));
    }
    return mat;
}

// Function to allocate memory for vector
double* allocateVector(int size) {
    double* vec = (double*)malloc(size * sizeof(double));
    return vec;
}

// Function to generate random values for matrix and vector
void generateRandom(double** mat, double* vec, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = (double)rand() / RAND_MAX; // Random value between 0 and 1
        }
    }
    for (int i = 0; i < cols; i++) {
        vec[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }
}

// Function to perform matrix-vector multiplication with tiling
double* matrixVectorMultiplicationTiled(double** mat, double* vec, int rows, int cols) {
    double* result = allocateVector(rows);
    #pragma omp parallel for
    for (int i = 0; i < rows; i += TILE_SIZE) {
        for (int j = 0; j < cols; j += TILE_SIZE) {
            for (int ii = i; ii < i + TILE_SIZE && ii < rows; ii++) {
                for (int jj = j; jj < j + TILE_SIZE && jj < cols; jj++) {
                    result[ii] += mat[ii][jj] * vec[jj];
                }
            }
        }
    }
    return result;
}

// Function to deallocate memory for matrix
void deallocateMatrix(double** mat, int rows) {
    for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Function to deallocate memory for vector
void deallocateVector(double* vec) {
    free(vec);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <matrix_size> <vector_size>\n", argv[0]);
        return 1;
    }
    int matrix_size = atoi(argv[1]);
    int vector_size = atoi(argv[2]);

    // Allocate memory for matrix and vector
    double** matrix = allocateMatrix(matrix_size, vector_size);
    double* vector = allocateVector(vector_size);

    // Generate random values for matrix and vector
    generateRandom(matrix, vector, matrix_size, vector_size);

    // Perform matrix-vector multiplication with tiling
    double* result = matrixVectorMultiplicationTiled(matrix, vector, matrix_size, vector_size);

    // Display result
    printf("Resultant Vector:\n");
    for (int i = 0; i < matrix_size; i++) {
        printf("%f ", result[i]);
    }
    printf("\n");

    // Deallocate memory
    deallocateMatrix(matrix, matrix_size);
    deallocateVector(vector);
    free(result);

    return 0;
}
