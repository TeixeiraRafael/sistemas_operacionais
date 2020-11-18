#include <time.h>
#include "lib/helpers.h"

int** random_matrix(int m, int n){
    int** matrix;
    matrix = malloc(m * n * sizeof(int));
    for(int i = 0; i < m; i++){
        int* rand;
        rand = random_array(n);
        matrix[i] = rand;
    }
    return matrix;
}


int multiply_and_sum(int* a, int* b, int size){
    int sum = 0;
    for(int i = 0; i < size; i ++){
        sum += (a[i] * b[i]);
    }
}

int main(int argc, char **argv){
    srand(time(NULL));
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
    int p = atoi(argv[3]);
    int q = atoi(argv[4]);
    int n_threads = atoi(argv[5]);

    int** A;
    int** B;
    A = random_matrix(m, n);
    
    printf("A:\n");
    for(int i = 0; i < m; ++i){
        printf("\t");
        for(int j = 0; j < n; ++j){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nB:\n");
    B = random_matrix(m, n);
    for(int i = 0; i < m; ++i){
        printf("\t");
        for(int j = 0; j < n; ++j){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}