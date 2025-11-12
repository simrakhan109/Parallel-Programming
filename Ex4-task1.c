#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Define matrix size and thread count directly in the code
#define N 700
#define THREADS 2

int main(int argc, char* argv[]) {
    int i, j, k;
    
    // Allocate dynamically
    // For my understanding: Here, we make space for N × N numbers (each of size double).
    double *a = (double*) malloc(N * N * sizeof(double));
    double *b = (double*) malloc(N * N * sizeof(double));
    double *c = (double*) malloc(N * N * sizeof(double));
    
    // For my understanding: Checks if memory allocation failed
    if (!a || !b || !c) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Initialize matrices
    // For my understanding: So we use math to jump to the correct position:
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i * N + j] = 3.0 * i + j;
            b[i * N + j] = 5.2 * i + 2.3 * j;
            c[i * N + j] = 0.0;
        }
    }
    
    omp_set_num_threads(THREADS);
    
    // For my understanding: omp_get_wtime() gives the current wall-clock time (in seconds).
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
    
    // Optional result validation
    double sum = 0.0;
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            sum += c[i * N + j];
    
    printf("Result sum: %f\n", sum);
    printf("Matrix size: %d x %d, Threads: %d, Time: %.6f seconds\n",
           N, N, THREADS, end - start);
    
    // For my understanding: Frees the memory we got from malloc() — important to avoid memory leaks.
    free(a);
    free(b);
    free(c);
    return 0;
}