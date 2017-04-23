/**
 * A solution to the pid manager problem. 
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>

/**
 * Allocates the pid map.
 */
int allocate_map(void) 
{
int i;

	for (i = PID_MIN; i <= PID_MAX; i++)
		pid_map[i] = 0;

	last = PID_MIN;

	return last;
}

/**
 * Allocates a pid
 */
int allocate_pid(void)
{
	int n_loops = 0;

	int next;

	if (last == PID_MAX)
		next = PID_MIN;
	else
		next = last + 1;

	/* find the next available pid */
	while ( (n_loops <= (PID_MAX - PID_MIN)) && (pid_map[next] == 1) ) {	
		++n_loops;
		++next;
		if (next > PID_MAX)
			next = PID_MIN;
	}

	if (n_loops == (PID_MAX - PID_MIN) + 1) {
		return -1;
	}
		
	/* we found one */
	pid_map[next] = 1;

	last = next;

	return last;
}

/**
 * Releases a pid
 */
void release_pid(int pid)
{
	pid_map[pid] = 0;
}
