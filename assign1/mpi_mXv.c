#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

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

// Function to perform matrix-vector multiplication
double* matrixVectorMultiplication(double** mat, double* vec, double* local_result, int local_rows, int cols) {
    for (int i = 0; i < local_rows; i++) {
        local_result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            local_result[i] += mat[i][j] * vec[j];
        }
    }
    return local_result;
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

    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Determine number of rows per process
    int rows_per_process = matrix_size / world_size;
    int remainder_rows = matrix_size % world_size;
    int* rows_counts = (int*)malloc(world_size * sizeof(int));
    int* rows_displs = (int*)malloc(world_size * sizeof(int));
    for (int i = 0; i < world_size; i++) {
        rows_counts[i] = rows_per_process;
        if (i < remainder_rows) {
            rows_counts[i]++;
        }
        rows_displs[i] = (i == 0) ? 0 : (rows_displs[i - 1] + rows_counts[i - 1]);
    }

    // Allocate memory for matrix and vector
    double** matrix;
    double* vector;
    if (world_rank == 0) {
        matrix = allocateMatrix(matrix_size, vector_size);
        vector = allocateVector(vector_size);
        generateRandom(matrix, vector, matrix_size, vector_size);
    }

    // Scatter matrix rows and broadcast vector
    double* local_matrix = allocateMatrix(rows_counts[world_rank], vector_size);
    MPI_Scatterv(matrix[0], rows_counts, rows_displs, MPI_DOUBLE, local_matrix[0], rows_counts[world_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector, vector_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Perform local matrix-vector multiplication
    double* local_result = allocateVector(rows_counts[world_rank]);
    matrixVectorMultiplication(local_matrix, vector, local_result, rows_counts[world_rank], vector_size);

    // Gather local results
    double* result;
    if (world_rank == 0) {
        result = allocateVector(matrix_size);
    }
    MPI_Gatherv(local_result, rows_counts[world_rank], MPI_DOUBLE, result, rows_counts, rows_displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Display result
    if (world_rank == 0) {
        printf("Resultant Vector:\n");
        for (int i = 0; i < matrix_size; i++) {
            printf("%f ", result[i]);
        }
        printf("\n");
    }

    // Deallocate memory
    if (world_rank == 0) {
        deallocateMatrix(matrix, matrix_size);
        deallocateVector(vector);
    }
    deallocateMatrix(local_matrix, rows_counts[world_rank]);
    deallocateVector(local_result);
    if (world_rank == 0) {
        free(result);
    }

    MPI_Finalize();

    return 0;
}
