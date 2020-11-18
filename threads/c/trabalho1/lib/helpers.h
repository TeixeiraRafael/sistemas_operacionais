#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
/*
	The segment struct holds a portion of an array.
	Each thread inverts a single array segment.
*/
typedef struct segment{
	int thread_id;
	int size;
	int* values;
} Segment;

void print_array(int* arr, int size);
int* random_array(int size);

#endif