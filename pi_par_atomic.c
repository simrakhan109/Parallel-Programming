#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 1000000000;
double step;

int main() {
    int i;
    double pi, sum = 0.0;
    double start_time, end_time;
    int num_threads;
    
    step = 1.0 / (double) num_steps;
    
    start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        double partial_sum = 0.0;
        
        #pragma omp single
        num_threads = nt;
        
        // Cyclic distribution
        for (i = id; i < num_steps; i += nt) {
            double x = (i + 0.5) * step;
            partial_sum += 4.0 / (1.0 + x * x);
        }
        
        // Atomic operation - faster than critical for simple operations
        #pragma omp atomic
        sum += partial_sum;
    }
    
    pi = step * sum;
    
    end_time = omp_get_wtime();
    
    printf("Version: Atomic\n");
    printf("Number of threads: %d\n", num_threads);
    printf("Approximation of Pi: %.16f\n", pi);
    printf("Number of steps: %ld\n", num_steps);
    printf("Elapsed time: %.6f seconds\n", end_time - start_time);
    
    return 0;
}