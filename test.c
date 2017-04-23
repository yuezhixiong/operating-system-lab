/**
 * test.c
 *
 * Test the implementation of the pid manager.
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS	10
#define SLEEP		5

int in_use[PID_MAX + 1];

/**
 * mutex lock used when accessing data structure
 * to ensure there are no duplicate pid's in use.
 */
pthread_mutex_t test_mutex;

void *allocator(void *param)
{
	int i, pid;

	for (i = 0; i < ITERATIONS; i++) {
		/* sleep for a random period of time */
		sleep((int)(random() % SLEEP));

		/* allocate a pid */
		pid = allocate_pid();
		printf("allocated %d\n",pid);

		if (pid == -1)
			printf("No pid available\n");
		else {
			/* indicate in the in_use map the pid is in use */
			pthread_mutex_lock(&test_mutex);
			if (in_use[pid] == 1) {
				fprintf(stderr,"***PID ALREADY IN USE****\n");
			}
			else
				in_use[pid] = 1;

			pthread_mutex_unlock(&test_mutex);
		
			/* sleep for a random period of time */
			sleep((int)(random() % SLEEP));

			/* release the pid */
			release_pid(pid);
			pthread_mutex_lock(&test_mutex);
			in_use[pid] = 0;
			pthread_mutex_unlock(&test_mutex);
			
			printf("released %d\n",pid);
		}
	}
}

int main(void)
{
	int i;
	pthread_t tids[NUM_THREADS];

	for (i = 0; i <= PID_MAX; i++) {
		in_use[i] = 0;
	}

	pthread_mutex_init(&test_mutex, NULL);

	/* allocate the pid map */
	if (allocate_map() == -1)
		return -1;

	srandom((unsigned)time(NULL));

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_create(&tids[i], NULL, allocator, NULL);
	}

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

	printf("***DONE***\n");

	return 0;
}
