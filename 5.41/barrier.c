#include <stdio.h>
#include <errno.h>
#include "barrier.h"
#include <pthread.h>
#include <semaphore.h>

/* the number of threads to wait for */
int waiting_size;

/* the number of waiting threads */
int count;	

/* mutex lock to protect access to count */
pthread_mutex_t count_lock;

/* semaphore for signalling purposes */
sem_t semaphore;

/**
 * Initialize the barrier
 */
int barrier_init(int parties)
{
	if (pthread_mutex_init(&count_lock, NULL) != 0) {
		fprintf(stderr,"Unable to create mutex lock\n");
		return -1;
	}

	if ( sem_init(&semaphore, 0,0) == -1) {
		fprintf(stderr,"Unable to creare semaphore\n");
		return -1;
	}

	count = 0;

	waiting_size = parties;

	return 0;
}

/**
 * The barrier
 */
int wait_for_others()
{
	if (pthread_mutex_lock(&count_lock) != 0) {
		fprintf(stderr,"mutex lock error\n");
		return -1;
	}

	/* increment the number of waiting threads */
	count++;

	if (pthread_mutex_unlock(&count_lock) != 0) {
		fprintf(stderr,"mutex unlock error\n");
		return -1;
	}

	if (count == waiting_size)
		if (sem_post(&semaphore) != 0) {
			fprintf(stderr,"semaphore post error\n");
			return -1;
		}

	if (sem_wait(&semaphore) != 0) {
		fprintf(stderr,"semaphore wait error\n");
		return -1;
	}

	if (sem_post(&semaphore) != 0) {
		fprintf(stderr,"semaphore post error\n");
		return -1;
	}

	return 0;
}
