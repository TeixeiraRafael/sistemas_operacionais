#include "helpers.h"

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
	/*
		Declaring the entry pointer of the array as a static variable so it won't
		go out of scope when the stack frame of the function gets popped.
	*/	
	static int* array;
	array = (int*) malloc(size * sizeof(int));

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