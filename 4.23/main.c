/**
 * Parallel version of calculating Pi 
 * using OpenMP.
 *
 * Compilation:
 *	gcc -fopenmp main.c
 * 
 * Solution to exercise 4.23
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void worker(void);

#define NUMBER_OF_DARTS		50000000

/* the number of hits in the circle */
int circle_count = 0;

/*
 * Generates a double precision random number
 */
double random_double() 
{
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {
	int i;
	double estimated_pi;

	/* seed the random number generator */
	srandom((unsigned)time(NULL));
	
	#pragma omp parallel
	{
		worker();
	}
	
	
	/* estimate Pi */
	estimated_pi = 4.0 * circle_count / (NUMBER_OF_DARTS * omp_get_num_procs());
	
	printf("Pi = %f\n",estimated_pi);
	
	return 0;
}

void worker(void)
{
	int i;
	int hit_count = 0;
	double x,y;

	for (i = 0; i < NUMBER_OF_DARTS; i++) {
		
		/* generate random numbers between -1.0 and +1.0 (exclusive) */
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;
		
		if ( sqrt(x*x + y*y) < 1.0 )
			++hit_count;		
	}
	
	circle_count += hit_count;
	
	return;
}
