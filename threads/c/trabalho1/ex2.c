#include <time.h>
#include <pthread.h>
#include "lib/helpers.h"

typedef struct Pair
{
    int x;
    int y;
} Pair;

typedef struct Segment
{
    int thread_id;
    int size;
    Pair *pairs;
} Segment;

int **random_matrix(int m, int n)
{
    int **matrix;
    matrix = malloc(m * n * sizeof(int));

    for (int i = 0; i < m; i++)
    {
        int *rand;
        rand = random_array(n);
        matrix[i] = rand;
    }

    return matrix;
}

int multiply_and_sum(int *a, int *b, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += (a[i] * b[i]);
    }
}

/*
    Creates a representation of the resulting matrix in the form of a pair array kinda like this:
    {(0,0), (0,1) ... (0, n), (1, 0), (1, 1) ... (n, n)}
*/
Pair* squash_matrix(int l, int c){
    Pair* pairs;
    pairs = malloc((l*c) * sizeof(Pair));
    Pair* pair;
    int pair_count = 0;
    for(int i = 0; i < l; ++i){
        for(int j = 0; j < c; ++j){
            pair = malloc(sizeof(Pair));
            pair->x = i;
            pair->y = j;
            pairs[pair_count] = *pair;
            free(pair);
            pair_count++;
        }
    }

    return pairs;
}

Segment* split(int l, int c, int n){
    int segment_size = (int)((l*c) / n);
    int remainder = (int)((l*c) % n);
    Segment segments[n];
    
    int seg_fill = 0;
    Segment* seg;
    Pair* pairs = squash_matrix(l, c);
    int pair_index = 0;
    for(int s = 0; s < n; ++s){
        seg = malloc(sizeof(Segment));
        if(s < n - 1){
            seg->size = segment_size;
        }else{
            seg->size = segment_size + remainder;
        }
        seg->pairs = malloc(segment_size * sizeof(Pair));
        for(int i = 0; i < seg->size; ++i){
            seg->pairs[i] = pairs[pair_index];
            ++pair_index;
        }
    }
    return segments;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int p = atoi(argv[3]);
    int q = atoi(argv[4]);
    int n_threads = atoi(argv[5]);

    int **A;
    int **B;
    A = random_matrix(m, n);

    printf("A:\n");
    for (int i = 0; i < m; ++i)
    {
        printf("\t");
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nB:\n");
    B = random_matrix(p, q);
    for (int i = 0; i < m; ++i)
    {
        printf("\t");
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    if (n_threads > m * q)
    {
        n_threads = m * q;
    }

    int C[m][q];
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < q; ++j){
            
        }
    }

    return EXIT_SUCCESS;
}