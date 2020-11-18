#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

typedef struct segment{
	int thread_id;
	int rand1;
	int rand2;
} Segment;

void* invert(void* seg){
	Segment* segment;
	segment = (Segment*) seg;
	printf("Thread id: %d\nFirst random number is: %d\nSecond random number is: %d\n", segment->thread_id, segment->rand2, segment->rand2);
	
	return NULL;
}

int main(int argc, char** argv){
	srand(time(NULL));

	int array_size =  atoi(argv[1]);
	int n = atoi(argv[2]);
	
	printf("Generating random array of size %d:\n[", array_size);
	int array[array_size];
	for(int i=0; i < array_size; i++){
		int randnum = rand() % 10;
		array[i] = randnum;
		if(i < array_size-1)
			printf("%d, ", randnum);
		else
			printf("%d]\n", randnum);
	}

	printf("Splitting the vector and allocating %d threads.\n", n);
	pthread_t thread[n];
	Segment* seg;

	for(int i = 0; i < n; i++){
		seg = malloc(sizeof(Segment));
		seg->thread_id = i;
		seg->rand1 = i* (rand() % 7);
		seg->rand2 = n*(rand() % 9);
		pthread_create(&thread[i], NULL, &invert, (void *)seg);
	}
	
	pthread_exit(NULL);
	return 0;
}
