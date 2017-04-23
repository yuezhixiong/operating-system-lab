/**
 * Parallel version of calculcating Pi 
 * 
 * Solution to exercise 5.39
 * 
 * This is a modification to exercise 4.22 where circle_count
 * is protected with a mutex lock.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void *worker(void *param);

#define NUMBER_OF_DARTS		50000000
#define NUMBER_OF_THREADS	2

/* the number of hits in the circle */
int circle_count = 0;

/* mutex lock to protect circle_count */
pthread_mutex_t mutex;

/*
 * Generates a double precision random number
 */
double random_double() 
{
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {
	int darts_per_thread = NUMBER_OF_DARTS/ NUMBER_OF_THREADS;
	int i;
	
	double estimated_pi;
	
	pthread_t workers[NUMBER_OF_THREADS];

	pthread_mutex_init(&mutex,NULL);

	/* seed the random number generator */
	srandom((unsigned)time(NULL));

	for (i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&workers[i], 0, worker, &darts_per_thread);
	
	for (i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(workers[i],NULL);

	
	/* estimate Pi */
	estimated_pi = 4.0 * circle_count / NUMBER_OF_DARTS;

	printf("Pi = %f\n",estimated_pi);
	
	return 0;
}

void *worker(void *param)
{
	int number_of_darts;
	number_of_darts = *((int *)param);
	int i;
	int hit_count = 0;
	double x,y;
	
	for (i = 0; i < number_of_darts; i++) {
		
		/* generate random numbers between -1.0 and +1.0 (exclusive) */
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;
		
		if ( sqrt(x*x + y*y) < 1.0 )
			++hit_count;		
	}

	/* ensure we do not have a race condition on circle count */	
	pthread_mutex_lock(&mutex);
	circle_count += hit_count;
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(0);
}

