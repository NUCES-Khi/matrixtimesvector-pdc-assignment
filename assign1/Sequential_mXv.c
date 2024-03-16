#include <stdio.h>
#include <stdlib.h>

void matvec_multiply(double **mat, double *vec, double *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            result[i] += mat[i][j] * vec[j];
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Usage: %s <matrix_size> <vector_size>\n", argv[0]);
        return 1;
    }
   
    int matrix_size = atoi(argv[1]);
    int vector_size = atoi(argv[2]);
 
    // Allocate memory for matrix and vector
    double **matrix = (double**)malloc(matrix_size * sizeof(double*));
    for (int i = 0; i < matrix_size; i++) {
        matrix[i] = (double*)malloc(vector_size * sizeof(double));
    }
    double* vector = (double*)malloc(vector_size * sizeof(double));
    double* result = (double*)malloc(matrix_size * sizeof(double));

    // Generate random values for matrix and vector
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < vector_size; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX; // Random value between 0 and 1
        }
    }
    for (int i = 0; i < vector_size; i++) {
        vector[i] = (double)rand() / RAND_MAX; // Random value between 0 and 1
    }

    // Perform matrix-vector multiplication
    matvec_multiply(matrix, vector, result, matrix_size, vector_size);

    // Display result
    //printf("Execution time: %f seconds\n", cpu_time_used);
    printf("Resultant Vector:\n");
    for (int i = 0; i < matrix_size; i++) {
        printf("%f ", result[i]);
    }
    printf("\n");
    
    // Deallocate memory
    for (int i = 0; i < matrix_size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);
    
    return 0;
}

