/**
 * Script  for testing the barrier implementation.
 *
 * Usage:
 *	./testbarrier <number of threads.
 */

#include <pthread.h>
#include <stdio.h>
#include "barrier.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr,"Usage: ./testbarrier <number of threads>\n");
		return -1;
	}

	int i;
	int number = atoi(argv[1]);

	pthread_t workers[number];

	if ( barrier_init(atoi(argv[1])) != 0)
		return -1;

	for (i = 0; i < number; i++) {
		pthread_create(&workers[i], 0, worker, 0);
	}

	for (i = 0; i < number; i++)
		pthread_join(workers[i], 0);

	return 0;
}
