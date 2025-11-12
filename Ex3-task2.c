#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv) {
    #pragma omp parallel
    printf("I am parallel\n");
    
    printf("I am not parallel\n");
}
