#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Define matrix size - can be changed for different tests
#define N 1000

int main() {
    int i, j, k;
    int THREADS = omp_get_max_threads(); // Will use OMP_NUM_THREADS from SLURM
    
    printf("Starting matrix multiplication with N=%d\n", N);
    printf("Number of threads: %d\n", THREADS);
    
    // Allocate dynamically
    double *a = (double*) malloc(N * N * sizeof(double));
    double *b = (double*) malloc(N * N * sizeof(double));
    double *c = (double*) malloc(N * N * sizeof(double));
    
    // Check if memory allocation failed
    if (!a || !b || !c) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Initialize matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i * N + j] = 3.0 * i + j;
            b[i * N + j] = 5.2 * i + 2.3 * j;
            c[i * N + j] = 0.0;
        }
    }
    
    double start = omp_get_wtime();
    
    // Parallel matrix multiplication
    #pragma omp parallel for private(j,k) schedule(static)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            double sum_ij = 0.0;
            for (k = 0; k < N; ++k) {
                sum_ij += a[i * N + k] * b[k * N + j];
            }
            c[i * N + j] = sum_ij;
        }
    }
    
    double end = omp_get_wtime();
    
    // Result validation
    double sum = 0.0;
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            sum += c[i * N + j];
    
    printf("Result sum: %f\n", sum);
    printf("Matrix size: %d x %d, Threads: %d, Time: %.6f seconds\n",
           N, N, THREADS, end - start);
    
    free(a);
    free(b);
    free(c);
    return 0;
}