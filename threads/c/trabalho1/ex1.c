#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include "lib/helpers.h"

/*
	Inverts the values of a given segment
	Receibes a void pointer that is cast to a Segment pointer to supress some compiler warnings.
*/
void *invert(void *seg)
{
	Segment *segment = (Segment *)seg;
	int temp;
	int start = 0;
	int end = segment->size - 1;

	while (start < end)
	{
		temp = segment->values[start];
		segment->values[start] = segment->values[end];
		segment->values[end] = temp;
		start++;
		end--;
	}

	return NULL;
}

/*
	Splits the given array in n equal segments.
	The last segment also carries the remainder of the division if necessary.
*/
Segment *split(int *array, int n, int size)
{
	Segment *segments;
	int segment_size = (int)(size / n);
	int remainder = (int)(size % n);

	segments = malloc(n * sizeof(Segment));
	int arr_index = 0;

	Segment *seg;
	for (int i = 0; i < n; ++i)
	{
		seg = malloc(sizeof(Segment));
		seg->thread_id = i;

		if (i < n - 1)
			seg->size = segment_size;
		else
			seg->size = segment_size + remainder;

		seg->values = malloc(segment_size * sizeof(int));

		for (int j = 0; j < seg->size; ++j)
		{
			seg->values[j] = array[arr_index];
			arr_index++;
		}
		segments[i] = *seg;
		free(seg);
	}
	return segments;
}

/*
	Reassambles a list of segments into a single unidimentional array (makes printing easier).
*/
int *reassamble(Segment *segments, int n_segments, int final_size)
{
	int *result = malloc(final_size * sizeof(int));
	int i = 0;
	for (int j = n_segments - 1; j >= 0; --j)
	{
		for (int k = 0; k < segments[j].size; ++k)
		{
			result[i] = segments[j].values[k];
			i++;
		}
	}
	return result;
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
	print_array(arr, array_size);

	Segment *segments = split(arr, n, array_size);
	pthread_t threads[n];

	for (int i = 0; i < n; ++i)
	{
		pthread_create(&threads[n], NULL, &invert, (void *)&segments[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		pthread_join(threads[n], NULL);
	}

	int *inverted;
	inverted = reassamble(segments, n, array_size);
	print_array(inverted, array_size);

	free(segments);
	return EXIT_SUCCESS;
}