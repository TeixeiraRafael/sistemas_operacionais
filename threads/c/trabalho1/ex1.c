#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

/*
	The segment struct holds a portion of an array.
	Each thread inverts a single array segment.
*/
typedef struct arg_struct{
	int array_size;
	int start;
	int end;
	
	int* arr;
	int* inverted;
} arg_struct;


void print_array(int* arr, int size){
	printf("[");
	for(int i = 0; i < size; i++){
		if(i < size-1)
			printf("%d, ", arr[i]);
		else
			printf("%d]\n", arr[i]);
	}	
}

int* random_array(int size){
	int* array;
	array = malloc(size * sizeof(int));

	if(array == NULL){
		printf("Malloc failed");
		return NULL;
	} else {
		for(int i=0; i < size; i++){
			array[i] = (rand() % 10);
		}
		return array;
	}
}


void *invert(void* arguments)
{
	arg_struct* args = (arg_struct*)arguments;
	
	int start = args->start;
	int end = args->end;
	int size = end - start + 1;
	int array_size = args->array_size;

	int relative_start = (size - start - 1);
	int relative_position, temp;

	for(int i = start; i <= end; ++i){
		relative_position = array_size - i - 1;
		args->inverted[relative_position] = args->arr[i];
	}
	return NULL;
}


/*Driver code*/
int main(int argc, char **argv)
{
	srand(time(NULL));
	int array_size = atoi(argv[1]);
	int n = atoi(argv[2]);

	//Optimizes the number of threads
	if (n > array_size)
	{
		n = array_size;
	}

	int *arr = random_array(array_size);
	int *inverted = malloc(array_size * sizeof(int));

	print_array(arr, array_size);

	pthread_t threads[n];
	
	int segment_size = (int)(array_size / n);
	int remainder = (int)(array_size % n);	
	
	int start = 0;
	int end = -1;

	arg_struct args[n];
	for (int i = 0; i < n; ++i)
	{
		if(i == n - 1){ //last segment carries the remainder
			segment_size += remainder;
		}
		end += segment_size;
		
		args[i].start = start;
		args[i].end = end;
		args[i].arr = arr;
		args[i].inverted = inverted;
		args[i].array_size = array_size;

		pthread_create(&threads[i], NULL, &invert, (void*)(&args[i]));
		start = end + 1;
	}
	for(int i = 0; i < n; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	print_array(inverted, array_size);

	return EXIT_SUCCESS;
}