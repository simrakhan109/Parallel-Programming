#include <stdio.h>
#include <omp.h>

int main() {
    printf("Before parallel region\n");
    printf("---\n");
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello World from thread %d of %d!\n", thread_id, total_threads);
    }
    
    printf("---\n");
    printf("After parallel region\n");
    return 0;
}