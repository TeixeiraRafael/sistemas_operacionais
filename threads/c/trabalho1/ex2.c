#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Pair
{
    int x;
    int y;
} Pair;

typedef struct arg_struct
{
    int thread_id, start, end, n, p;
    Pair *map;
    int **A;
    int **B;
    int **C;
} arg_struct;

void print_matrix(int **A, int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        printf("\t");
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
int **random_matrix(int m, int n)
{
    int *r;
    int **matrix;
    matrix = malloc(m * n * sizeof(int));

    for (int i = 0; i < m; ++i)
    {
        r = malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j)
        {
            r[j] = (int)(rand() % 10);
        }
        matrix[i] = r;
    }

    return matrix;
}
/*
    Returns de sum of the products of the items of two integer arrays
*/
int multiply_and_sum(int *a, int *b, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += (a[i] * b[i]);
    }
    return sum;
}

/*
    Creates a representation of the resulting matrix in the form of a index pair array kinda like this:
    {(0,0), (0,1) ... (0, n), (1, 0), (1, 1) ... (n, n)}
*/
Pair *squash_matrix(int l, int c)
{
    Pair *pairs;
    pairs = malloc((l * c) * sizeof(Pair));
    Pair *pair;
    int pair_count = 0;
    for (int i = 0; i < l; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
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

void *process(void *arguments)
{
    arg_struct *args = (arg_struct *)arguments;
    int *line;
    int *column;
    int n = args->n;
    int p = args->p;
    int start = args->start;
    int end = args->end;
    Pair *map = args->map;
    int **A = args->A;
    int **B = args->B;
    int **C = args->C;

    for (int i = start; i <= end; ++i)
    {
        line = malloc(n * sizeof(int));
        column = malloc(p * sizeof(int));
        for (int j = 0; j < n; ++j)
        {
            line[j] = A[map[i].x][j];
        }
        for (int k = 0; k < p; ++k)
        {
            column[k] = B[k][map[i].y];
        }
        C[map[i].x][map[i].y] = multiply_and_sum(line, column, n);
        free(line);
        free(column);
    };
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
    int **C = random_matrix(m, q);

    A = random_matrix(m, n);

    printf("A:\n");
    print_matrix(A, m, n);
    printf("\nB:\n");
    B = random_matrix(p, q);
    print_matrix(B, p, q);

    if (n_threads > m * q)
    {
        n_threads = m * q;
    }

    Pair *index_map = squash_matrix(m, q);
    pthread_t threads[n_threads];
    arg_struct *args;

    int segment_size = (int)(m * q) / n_threads;
    int remainder = (int)(m * q) % n_threads;
    int start = 0;
    int end = -1;

    for (int i = 0; i < n_threads; ++i)
    {
        if (i == n_threads - 1) //last segment carries the remainder
        { 
            segment_size += remainder;
        }
        end += segment_size;

        args = malloc(sizeof(arg_struct));
        args->thread_id = i;
        args->n = n;
        args->p = p;
        args->start = start;
        args->end = end;
        args->map = index_map;
        args->A = A;
        args->B = B;
        args->C = C;

        pthread_create(&threads[i], NULL, &process, (void *)args);

        start = end + 1;
    }

    for (int i = 0; i < n_threads; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    free(args);
    printf("C:\n");
    print_matrix(C, m, q);
    return EXIT_SUCCESS;
}
